// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"


// 플레이어 잡힘 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerCaught);

UCLASS()
class UE_STEALTHAI_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()


public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	
	// 현재 순찰 목표 인덱스
	int32 CurrentPatrolPointIndex = 0;

	// 목적지 도착 확인
	bool HasReachedDestination() const;

	// 플레이어 잡힘 이벤트
	UPROPERTY(BlueprintAssignable, Category = "GameRules")
	FOnPlayerCaught OnPlayerCaught;

private:
	
	// 플레이어 감지 함수
	void DetectPlayer();

	// 시야 범위 안에 플레이어가 있는지 확인
	bool IsPlayerInSight() const;

	// 빙의된 EnemyCharacter 포인터
	class AEnemyCharacter* EnemyCharacter = nullptr;

	// 감지된 플레이어 포인터
	class AStealthCharacter* TargetPlayer = nullptr;
};
