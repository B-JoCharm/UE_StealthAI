// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "StealthCharacter.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(InPawn))
    {
        EnemyCharacter = Enemy;

        if (Enemy->BehaviorTreeAsset)
        {
            RunBehaviorTree(Enemy->BehaviorTreeAsset);
        }
    }
}

void AEnemyAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!TargetPlayer)
    {
        TargetPlayer = Cast<AStealthCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    }

    DetectPlayer();
}

bool AEnemyAIController::HasReachedDestination() const
{
    if (GetPathFollowingComponent() == nullptr) return false;

    EPathFollowingStatus::Type Status = GetPathFollowingComponent()->GetStatus();
    return Status == EPathFollowingStatus::Idle;
}

void AEnemyAIController::DetectPlayer()
{
    if (!EnemyCharacter) return;

    if (IsPlayerInSight())
    {
        EnemyCharacter->AIState = EAIState::Chase;
        EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = EnemyCharacter->ChaseSpeed;

        if (GetBlackboardComponent())
        {
            GetBlackboardComponent()->SetValueAsObject(TEXT("TargetPlayer"), TargetPlayer);
        }

        if (TargetPlayer)
        {
            float DistToPlayer = FVector::Dist(EnemyCharacter->GetActorLocation(), TargetPlayer->GetActorLocation());
            if (DistToPlayer < EnemyCharacter->CatchDistance)
            {
                OnPlayerCaught.Broadcast();
            }
        }
    }
    else
    {
        if (GetBlackboardComponent())
        {
            GetBlackboardComponent()->ClearValue(TEXT("TargetPlayer"));
        }

        if (EnemyCharacter->AIState == EAIState::Chase)
        {
            EnemyCharacter->AIState = EAIState::Patrol;
            EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = EnemyCharacter->PatrolSpeed;
        }
    }
}

bool AEnemyAIController::IsPlayerInSight() const
{
    if (!EnemyCharacter) return false;
    if (!TargetPlayer) return false;

    float Distance = FVector::Dist(EnemyCharacter->GetActorLocation(), TargetPlayer->GetActorLocation());
    if (Distance > EnemyCharacter->DetectionRange) return false;

    FVector DirectionToPlayer = (TargetPlayer->GetActorLocation() - EnemyCharacter->GetActorLocation()).GetSafeNormal();
    FVector EnemyForward = EnemyCharacter->GetActorForwardVector();
    float DotProduct = FVector::DotProduct(EnemyForward, DirectionToPlayer);
    float AngleInDegrees = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

    if (AngleInDegrees > EnemyCharacter->DetectionAngle) return false;

    FHitResult HitResult;
    FVector Start = EnemyCharacter->GetActorLocation();
    FVector End = TargetPlayer->GetActorLocation();
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(EnemyCharacter);

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

    return !bHit;
}
