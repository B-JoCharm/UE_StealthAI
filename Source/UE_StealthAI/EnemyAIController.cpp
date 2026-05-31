// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyCharacter.h"

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 빙의된 캐릭터가 AEnemyCharacter인지 확인
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(InPawn))
	{

	}
}

