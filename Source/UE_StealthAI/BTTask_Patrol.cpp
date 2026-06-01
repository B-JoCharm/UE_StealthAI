// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTTask_Patrol::UBTTask_Patrol()
{
    NodeName = TEXT("Patrol");
    bNotifyTick = true; // Tick 활성화
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    if (!AIController) return EBTNodeResult::Failed;

    AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIController->GetPawn());
    if (!Enemy) return EBTNodeResult::Failed;

    if (Enemy->PatrolPoints.Num() == 0) return EBTNodeResult::Failed;

    AActor* TargetPoint = Enemy->PatrolPoints[AIController->CurrentPatrolPointIndex];
    AIController->MoveToActor(TargetPoint, 50.f);

    return EBTNodeResult::InProgress;
}


void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AEnemyAIController* AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    if (!AIController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    if (AIController->HasReachedDestination())
    {
        AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(AIController->GetPawn());
        if (Enemy)
        {
            // 도착 후 인덱스 업데이트
            AIController->CurrentPatrolPointIndex = (AIController->CurrentPatrolPointIndex + 1) % Enemy->PatrolPoints.Num();
        }
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}