// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "StageManager.generated.h"

class UStealthSaveGame;

UCLASS()
class UE_STEALTHAI_API UStageManager : public UObject
{
	GENERATED_BODY()

public:
	UStageManager();

	// 초기화 - GameInstance에서 호출
	void Initialize();

	// AssetRegistry로 StageMap 목록 스캔
	void ScanStages();

	// 스테이지 잠금 여부
	bool IsStageUnlocked(int32 World, int32 Stage) const;

	// 현재 스테이지 클리어 처리
	void ClearCurrentStage();

	// 다음 스테이지 로드
	void LoadNextStage(UObject* WorldContext);

	// 특정 스테이지 로드
	UFUNCTION(BlueprintCallable, Category = "Stage")
	void LoadStage(int32 World, int32 Stage, UObject* WorldContext);

	// 세이브/로드
	void SaveGame();

	UFUNCTION(BlueprintCallable, Category = "Stage")
	void LoadGame();

	UFUNCTION(BlueprintCallable, Category = "Stage")
	int32 GetCurrentWorld() const { return CurrentWorld; }

	UFUNCTION(BlueprintCallable, Category = "Stage")
	int32 GetCurrentStage() const { return CurrentStage; }

private:
	// Key: "World-Stage" (예: "1-1"), Value: 맵 경로
	TMap<FString, FString> StageMap;

	int32 CurrentWorld = 1;
	int32 CurrentStage = 1;

	UPROPERTY()
	UStealthSaveGame* CurrentSaveGame;
};
