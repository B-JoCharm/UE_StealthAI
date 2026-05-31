// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE_STEALTHAI_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()


public:
	virtual void OnPossess(APawn* InPawn) override;
};
