// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StealthGameInstance.generated.h"

/**
 * 
 */
class UStageManager;

UCLASS()
class UE_STEALTHAI_API UStealthGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	UStageManager* GetStageManager() const { return StageManager; }

private:
	UPROPERTY()
	UStageManager* StageManager;
};
