// Fill out your copyright notice in the Description page of Project Settings.

#include "StealthGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAIController.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "Framework/Application/SlateApplication.h"
#include "Engine/GameViewportClient.h"

void AStealthGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimerForNextTick([this]()
        {
            if (UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport())
            {
                ViewportClient->SetMouseCaptureMode(EMouseCaptureMode::CapturePermanently);
                ViewportClient->SetHideCursorDuringCapture(true);
                FSlateApplication::Get().SetAllUserFocusToGameViewport();
            }
        });

    for (TActorIterator<AEnemyAIController> It(GetWorld()); It; ++It)
    {
        It->OnPlayerCaught.AddDynamic(this, &AStealthGameModeBase::OnPlayerCaughtHandler);
    }
}

void AStealthGameModeBase::OnGameWin()
{
    if (bGameOver) return;
    bGameOver = true;

    if (GameWinWidgetClass)
    {
        ActiveGameWinWidget = CreateWidget<UUserWidget>(GetWorld(), GameWinWidgetClass);
        if (ActiveGameWinWidget)
        {
            ActiveGameWinWidget->AddToViewport();
        }
    }

    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        FInputModeUIOnly InputMode;
        PC->SetInputMode(InputMode);
        PC->bShowMouseCursor = true;
    }
}

void AStealthGameModeBase::OnGameLose()
{
    if (bGameOver) return;
    bGameOver = true;

    if (GameLoseWidgetClass)
    {
        UUserWidget* GameLoseWidget = CreateWidget<UUserWidget>(GetWorld(), GameLoseWidgetClass);
        if (GameLoseWidget)
        {
            GameLoseWidget->AddToViewport();
        }
    }

    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        FInputModeUIOnly InputMode;
        PC->SetInputMode(InputMode);
        PC->bShowMouseCursor = true;
    }
}

void AStealthGameModeBase::RestartGame()
{
    bGameOver = false;
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        PC->bShowMouseCursor = false;
    }
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AStealthGameModeBase::OnPlayerCaughtHandler()
{
    OnGameLose();
}

void AStealthGameModeBase::NextStage()
{
    if (ActiveGameWinWidget)
    {
        ActiveGameWinWidget->RemoveFromParent();
        ActiveGameWinWidget = nullptr;
    }

    bGameOver = false;

    UStealthGameInstance* GI = Cast<UStealthGameInstance>(UGameplayStatics::GetGameInstance(this));
    if (GI && GI->GetStageManager())
    {
        GI->GetStageManager()->ClearCurrentStage();
        GI->GetStageManager()->LoadNextStage(this);
    }
}
