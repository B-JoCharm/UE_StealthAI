// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Patrol	 UMETA(DisplayName = "Patrol"),
	Chase	 UMETA(DisplayName = "Chase"),
	Search	 UMETA(DisplayName = "Search"),
};

UCLASS()
class UE_STEALTHAI_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	// 현재 AI 상태
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	EAIState AIState = EAIState::Patrol;

	// 이동 속도
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement")
	float PatrolSpeed = 200.f; 

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement")
	float ChaseSpeed = 400.f;

	// 감지 거리 (BP에서 튜닝 가능)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	float DetectionRange = 1000.f;

	// 시야 각 (BP에서 튜닝 가능)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	float DetectionAngle = 60.f;

	// 순찰 포인트 배열 (BP에서 할당)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TArray<AActor*> PatrolPoints;

	// Behavior Tree 에셋 (BP에서 할당)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* BehaviorTreeAsset;

	// 플레이어 감지 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
	float CatchDistance = 150.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
