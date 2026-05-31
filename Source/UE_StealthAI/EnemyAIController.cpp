// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "Engine/TargetPoint.h"
#include "Navigation/PathFollowingComponent.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 빙의된 캐릭터가 AEnemyCharacter인지 확인
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(InPawn))
	{
		EnemyCharacter = Enemy;
		MoveToNextPatrolPoint();
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (EnemyCharacter && HasReachedDestination())
	{
		MoveToNextPatrolPoint();
	}
}

void AEnemyAIController::MoveToNextPatrolPoint()
{
	if (!EnemyCharacter) return;
	if (EnemyCharacter->PatrolPoints.Num() == 0) return;
	
	AActor* TargetPoint = EnemyCharacter->PatrolPoints[CurrentPatrolPointIndex];
	MoveToActor(TargetPoint, 50.f); // 50.f는 도착 허용 반경입니다.

	// 순찰 포인트 인덱스 업데이트
	CurrentPatrolPointIndex = (CurrentPatrolPointIndex + 1) % EnemyCharacter->PatrolPoints.Num();
}

bool AEnemyAIController::HasReachedDestination() const
{
	if (GetPathFollowingComponent() == nullptr) return false;

	EPathFollowingStatus::Type Status = GetPathFollowingComponent()->GetStatus();
	return Status == EPathFollowingStatus::Idle;
}

