// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StealthGameModeBase.generated.h"

UCLASS()
class UE_STEALTHAI_API AStealthGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:
	// 게임 승리 처리
	UFUNCTION(BlueprintCallable, Category = "GameRules")
	void OnGameWin();

	// 게임 오버 처리
	UFUNCTION(BlueprintCallable, Category = "GameRules")
	void OnGameLose();

	// 게임 재시작
	UFUNCTION(BlueprintCallable, Category = "GameRules")
	void RestartGame();

	// EnemyAIController의 OnPlayerCaught 델리게이트 바인딩
	UFUNCTION()
	void OnPlayerCaughtHandler();

	// 승리 UI 위젯 클래스 (BP에서 할당)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> GameWinWidgetClass;

	// 패배 UI 위젯 클래스 (BP에서 할당)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> GameLoseWidgetClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 게임 승리/오버 상태
	bool bGameOver = false;

};
