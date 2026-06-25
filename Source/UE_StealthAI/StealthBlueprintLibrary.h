// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnemyCharacter.h"
#include "StealthBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UE_STEALTHAI_API UStealthBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category = "AI", meta = (DisplayName = "Equal (EAIState)", CompactNodeTitle = "=="))
    static bool EqualEqual_AIState(EAIState A, EAIState B) { return A == B; }
};
