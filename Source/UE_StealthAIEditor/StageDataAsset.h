// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyCharacter.h"
#include "ObjectiveActor.h"
#include "StageDataAsset.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnemySpawnData
{
	GENERATED_BODY()

	// BP_EnemyCharacter를 위한 AEnemyCharacter 기반 클래스 지정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TSubclassOf<AEnemyCharacter> EnemyClass;

	// 스폰 위치, 회전, 스케일
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FTransform SpawnTransform;

	// 해당 Enemy의 순찰포인트 위치 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	TArray<FVector> PatrolPoints;
};

// 스테이지 하나의 전체 데이터를 담는 Data Asset 클래스
// 기획자가 에디터에서 편집 가능
UCLASS(BlueprintType)
class UE_STEALTHAIEDITOR_API UStageDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	// 스테이지 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	FString StageName;

	// 스테이지에서 로드할 맵 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	FName MapName;

	// 이 스테이지에 배치할 Enemy 목록
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	TArray<FEnemySpawnData> EnemySpawns;

	// 목표 지점 BP 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	TSubclassOf<AObjectiveActor> ObjectiveClass;

	// 목표 지점(ObjectiveActor)의 위치, 회전, 스케일
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	FTransform ObjectiveTransform;

	// EUW 드롭다운에 표시할 사용 가능한 Enemy 클래스 목록
	// BP_EnemyCharacter등을 이곳에 등록해서 사용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	TArray<TSubclassOf<AEnemyCharacter>> AvailableEnemyClasses;

	// Wall BP 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	TSubclassOf<AActor> WallClass;

	// Box BP 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	TSubclassOf<AActor> BoxClass;
};

