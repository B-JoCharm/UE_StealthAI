// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "StealthCharacter.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 빙의된 캐릭터가 AEnemyCharacter인지 확인
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

	// TargetPlayer가 없으면 다시 찾기
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
		// 플레이어 발견 -> Chase 상태로 전환
		EnemyCharacter->AIState = EAIState::Chase;

		// Chase 속도로 전환
		EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = EnemyCharacter->ChaseSpeed;

		if(GetBlackboardComponent())
		{
			GetBlackboardComponent()->SetValueAsObject(TEXT("TargetPlayer"), TargetPlayer);
		}
	}
	else
	{
		// 플레이어 시야에서 사라짐 -> Blackboard에서 TargetPlayer 제거
		if(GetBlackboardComponent())
		{
			GetBlackboardComponent()->ClearValue(TEXT("TargetPlayer"));
		}

		// Patrol 상태로 전환
		if (EnemyCharacter->AIState == EAIState::Chase)
		{
			EnemyCharacter->AIState = EAIState::Patrol;

			// Patrol 속도로 전환
			EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = EnemyCharacter->PatrolSpeed;
		}
	}
}

bool AEnemyAIController::IsPlayerInSight() const
{
	if (!EnemyCharacter) return false;
	if (!TargetPlayer) return false;

	// 거리 확인
	float Distance = FVector::Dist(EnemyCharacter->GetActorLocation(), TargetPlayer->GetActorLocation());
	if (Distance > EnemyCharacter->DetectionRange) return false;

	// 시야 각 확인
	FVector DirectionToPlayer = (TargetPlayer->GetActorLocation() - EnemyCharacter->GetActorLocation()).GetSafeNormal();
	FVector EnemyForward = EnemyCharacter->GetActorForwardVector();
	float DotProduct = FVector::DotProduct(EnemyForward, DirectionToPlayer);
	float AngleInDegrees = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

	if (AngleInDegrees > EnemyCharacter->DetectionAngle) return false;

	// LineTrace로 시야에 장애물이 없는지 확인
	FHitResult HitResult;
	FVector Start = EnemyCharacter->GetActorLocation();
	FVector End = TargetPlayer->GetActorLocation();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(EnemyCharacter); // 자기 자신은 무시

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

	// 디버그 라인 그리기
	DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Red : FColor::Green, false, 0.1f);

	if (!bHit)
	{
		return true;
	}
	return false;
}

