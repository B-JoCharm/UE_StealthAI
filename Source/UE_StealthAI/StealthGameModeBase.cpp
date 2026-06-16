// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAIController.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

void AStealthGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    // 맵의 모든 EnemyAIController에 델리게이트 바인딩
    for (TActorIterator<AEnemyAIController> It(GetWorld()); It; ++It)
    {
		It->OnPlayerCaught.AddDynamic(this, &AStealthGameModeBase::OnPlayerCaughtHandler);
	}
}

void AStealthGameModeBase::OnGameWin()
{
    if (bGameOver) return;
    bGameOver = true;

    UE_LOG(LogTemp, Warning, TEXT("Game Win!"));

    // 승리 UI 표시
    if (GameWinWidgetClass)
    {
        UUserWidget* GameWinWidget = CreateWidget<UUserWidget>(GetWorld(), GameWinWidgetClass);
        if (GameWinWidget)
        {
            GameWinWidget->AddToViewport();
		}
    }

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
		// UI 클릭을 위한 마우스 활성화
		PC->bShowMouseCursor = true;
    }
}

void AStealthGameModeBase::OnGameLose()
{
    if (bGameOver) return;
    bGameOver = true;

    UE_LOG(LogTemp, Warning, TEXT("Game Lose!"));

    // 패배 UI 표시
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
        // UI 클릭을 위한 마우스 활성화
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
	if (StageMapNames.Num() == 0) return;

    CurrentStageIndex++;

    // 마지막 스테이지면 처음으로 돌아가기
    if(CurrentStageIndex >= StageMapNames.Num())
    {
        CurrentStageIndex = 0;
	}

    bGameOver = false;
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        PC->bShowMouseCursor = false;
    }

	UGameplayStatics::OpenLevel(this, StageMapNames[CurrentStageIndex]);
}
