// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StageDataAsset.h"
#include "EnemyCharacter.h"
#include "ObjectiveActor.h"
#include "StageBuilderTool.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class UE_STEALTHAIEDITOR_API UStageBuilderTool : public UObject
{
	GENERATED_BODY()
	
public:
	// StageDataAsset 기반으로 현재 레벨에 모든 액터 배치
	UFUNCTION(BlueprintCallable, Category = "StageBuilder")
	void BuildStageFromData(UStageDataAsset* StageData);

	// Enemy 하나를 레벨에 배치
	UFUNCTION(BlueprintCallable, Category = "StageBuilder")
	AEnemyCharacter* SpawnEnemy(const FEnemySpawnData& EnemyData);

	// 목표 지점(ObjectiveActor) 하나를 레벨에 배치
	UFUNCTION(BlueprintCallable, Category = "StageBuilder")
	AObjectiveActor* SpawnObjective(TSubclassOf<AObjectiveActor> ObjectiveClass, FTransform ObjectiveTransform);

	// 클래스와 위치만 받아서 Enemy 스폰 (EUW 배치용)
	UFUNCTION(BlueprintCallable, Category = "StageBuilder")
	AEnemyCharacter* SpawnEnemyAtLocation(TSubclassOf<AEnemyCharacter> EnemyClass, FVector Location);

	// Wall을 레벨에 배치 (BP 기반)
	UFUNCTION(BlueprintCallable, Category = "StageBuilder")
	AActor* SpawnWall(TSubclassOf<AActor>WallClass, FVector Scale);

	// Box를 레벨에 배치 (BP 기반)
	UFUNCTION(BlueprintCallable, Category = "StageBuilder")
	AActor* SpawnBox(TSubclassOf<AActor> BoxClass, FVector Scale);
};
