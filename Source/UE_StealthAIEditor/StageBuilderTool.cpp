// Fill out your copyright notice in the Description page of Project Settings.


#include "StageBuilderTool.h"
#include "Editor/EditorEngine.h"
#include "Engine/World.h"

void UStageBuilderTool::BuildStageFromData(UStageDataAsset* StageData)
{
    if (!StageData) return;

    // 스테이지 프리셋 전체 불러오기 기능 구현 예정
}

AEnemyCharacter* UStageBuilderTool::SpawnEnemy(const FEnemySpawnData& EnemyData)
{
    if (!EnemyData.EnemyClass) return nullptr;

    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World) return nullptr;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // EnemyData.EnemyClass에 BP_EnemyCharacter를 지정하면
    // BP의 메시, BT 에셋, AIController 등 모든 설정이 그대로 적용됨
    return World->SpawnActor<AEnemyCharacter>(
        EnemyData.EnemyClass,
        EnemyData.SpawnTransform,
        SpawnParams
    );
}

AEnemyCharacter* UStageBuilderTool::SpawnEnemyAtLocation(TSubclassOf<AEnemyCharacter> EnemyClass, FVector Location)
{
    if (!EnemyClass) return nullptr;

    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World) return nullptr;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // 맵 중앙(0,0,0) 또는 지정된 위치에 스폰
    FTransform SpawnTransform(FRotator::ZeroRotator, Location);

    return World->SpawnActor<AEnemyCharacter>(
        EnemyClass,
        SpawnTransform,
        SpawnParams
    );
}

AObjectiveActor* UStageBuilderTool::SpawnObjective(TSubclassOf<AObjectiveActor> ObjectiveClass, FTransform ObjectiveTransform)
{
    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World) return nullptr;

    // ObjectiveClass가 지정되지 않으면 기본 AObjectiveActor 사용
    if (!ObjectiveClass)
    {
        ObjectiveClass = AObjectiveActor::StaticClass();
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    return World->SpawnActor<AObjectiveActor>(
        ObjectiveClass,
        ObjectiveTransform,
        SpawnParams
    );
}

AActor* UStageBuilderTool::SpawnWall(TSubclassOf<AActor> WallClass, FVector Scale)
{
    if (!WallClass) return nullptr;

    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World) return nullptr;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // 스케일 없이 먼저 스폰
    FTransform SpawnTransform;
    SpawnTransform.SetLocation(FVector::ZeroVector);

    AActor* SpawnedActor = World->SpawnActor<AActor>(WallClass, SpawnTransform, SpawnParams);

    // 스폰 후 스케일 적용
    if (SpawnedActor)
    {
        SpawnedActor->SetActorScale3D(Scale);
    }

    return SpawnedActor;
}

AActor* UStageBuilderTool::SpawnBox(TSubclassOf<AActor> BoxClass, FVector Scale)
{
    if (!BoxClass) return nullptr;

    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World) return nullptr;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // 스케일 없이 먼저 스폰
    FTransform SpawnTransform;
    SpawnTransform.SetLocation(FVector::ZeroVector);

    AActor* SpawnedActor = World->SpawnActor<AActor>(BoxClass, SpawnTransform, SpawnParams);

    // 스폰 후 스케일 적용
    if (SpawnedActor)
    {
        SpawnedActor->SetActorScale3D(Scale);
    }

    return SpawnedActor;
}

