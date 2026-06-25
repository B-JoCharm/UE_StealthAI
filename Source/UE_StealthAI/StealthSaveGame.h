// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "StealthSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UE_STEALTHAI_API UStealthSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	// 클리어한 스테이지 목록 ("1-1", "1-2"등)
	UPROPERTY(SaveGame)
	TSet<FString> ClearedStages;

	// 현재 스테이지 위치
	UPROPERTY(SaveGame)
	int32 CurrentWorld = 1;

	UPROPERTY(SaveGame)
	int32 CurrentStage = 1;
};
