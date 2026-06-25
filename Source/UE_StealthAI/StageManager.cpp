// Fill out your copyright notice in the Description page of Project Settings.

#include "StageManager.h"
#include "StealthSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "AssetRegistry/AssetRegistryModule.h"

static const FString SaveSlotName = TEXT("StealthSave");
static const int32 SaveUserIndex = 0;

UStageManager::UStageManager()
{
    CurrentSaveGame = nullptr;
    CurrentWorld = 1;
    CurrentStage = 1;
}

void UStageManager::Initialize()
{
    LoadGame();
    ScanStages();
}

void UStageManager::ScanStages()
{
    StageMap.Empty();

    IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

    // PIE/Standalone 모두에서 스캔 완료를 보장하는 강제 동기 스캔
    AssetRegistry.SearchAllAssets(true);

    TArray<FString> StageFolders;
    AssetRegistry.EnumerateSubPaths("/Game/Maps", [&](const FString& Path) -> bool
        {
            FString FolderName = FPaths::GetBaseFilename(Path);
            if (FolderName.StartsWith("Stage"))
            {
                StageFolders.Add(Path);
            }
            return true;
        }, false);

    for (const FString& Folder : StageFolders)
    {
        TArray<FAssetData> Assets;
        AssetRegistry.GetAssetsByPath(FName(*Folder), Assets, false);

        for (const FAssetData& Asset : Assets)
        {
            if (Asset.AssetClassPath.GetAssetName() == FName("World"))
            {
                FString FolderName = FPaths::GetBaseFilename(Folder);
                FString WorldNumStr = FolderName.RightChop(5); // "Stage" 제거
                int32 WorldNum = FCString::Atoi(*WorldNumStr);

                FString AssetName = Asset.AssetName.ToString();
                int32 DashIdx;
                if (AssetName.FindChar(TEXT('-'), DashIdx))
                {
                    FString StageNumStr = AssetName.RightChop(DashIdx + 1);
                    int32 StageNum = FCString::Atoi(*StageNumStr);

                    if (WorldNum > 0 && StageNum > 0)
                    {
                        FString Key = FString::Printf(TEXT("%d-%d"), WorldNum, StageNum);
                        FString PackageName = Asset.PackageName.ToString();
                        StageMap.Add(Key, PackageName);
                        UE_LOG(LogTemp, Log, TEXT("Stage Found: %s -> %s"), *Key, *PackageName);
                    }
                }
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("ScanStages Complete: %d stages found"), StageMap.Num());
}

bool UStageManager::IsStageUnlocked(int32 World, int32 Stage) const
{
    if (World == 1 && Stage == 1) return true;

    if (!CurrentSaveGame) return false;

    FString PrevKey;
    if (Stage > 1)
    {
        PrevKey = FString::Printf(TEXT("%d-%d"), World, Stage - 1);
    }
    else
    {
        return false;
    }

    return CurrentSaveGame->ClearedStages.Contains(PrevKey);
}

void UStageManager::ClearCurrentStage()
{
    if (!CurrentSaveGame) return;

    FString Key = FString::Printf(TEXT("%d-%d"), CurrentWorld, CurrentStage);
    CurrentSaveGame->ClearedStages.Add(Key);

    SaveGame();
}

void UStageManager::LoadNextStage(UObject* WorldContext)
{
    FString NextKey = FString::Printf(TEXT("%d-%d"), CurrentWorld, CurrentStage + 1);

    if (StageMap.Contains(NextKey))
    {
        LoadStage(CurrentWorld, CurrentStage + 1, WorldContext);
    }
    else
    {
        FString NextWorldKey = FString::Printf(TEXT("%d-%d"), CurrentWorld + 1, 1);
        if (StageMap.Contains(NextWorldKey))
        {
            LoadStage(CurrentWorld + 1, 1, WorldContext);
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("All stages cleared!"));
        }
    }
}

void UStageManager::LoadStage(int32 World, int32 Stage, UObject* WorldContext)
{
    FString Key = FString::Printf(TEXT("%d-%d"), World, Stage);

    if (!StageMap.Contains(Key))
    {
        UE_LOG(LogTemp, Warning, TEXT("Stage %s not found!"), *Key);
        return;
    }

    CurrentWorld = World;
    CurrentStage = Stage;

    FString MapPath = StageMap[Key];
    UGameplayStatics::OpenLevel(WorldContext, FName(*MapPath), true);
}

void UStageManager::SaveGame()
{
    if (!CurrentSaveGame)
    {
        CurrentSaveGame = Cast<UStealthSaveGame>(
            UGameplayStatics::CreateSaveGameObject(UStealthSaveGame::StaticClass()));
    }

    CurrentSaveGame->CurrentWorld = CurrentWorld;
    CurrentSaveGame->CurrentStage = CurrentStage;

    UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SaveSlotName, SaveUserIndex);
}

void UStageManager::LoadGame()
{
    if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, SaveUserIndex))
    {
        CurrentSaveGame = Cast<UStealthSaveGame>(
            UGameplayStatics::LoadGameFromSlot(SaveSlotName, SaveUserIndex));

        if (CurrentSaveGame)
        {
            CurrentWorld = CurrentSaveGame->CurrentWorld;
            CurrentStage = CurrentSaveGame->CurrentStage;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("SaveGame Cast Failed!"));
            CurrentWorld = 1;
            CurrentStage = 1;
        }
    }
    else
    {
        CurrentSaveGame = Cast<UStealthSaveGame>(
            UGameplayStatics::CreateSaveGameObject(UStealthSaveGame::StaticClass()));

        CurrentWorld = 1;
        CurrentStage = 1;
    }
}
