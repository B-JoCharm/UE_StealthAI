// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthGameInstance.h"
#include "StageManager.h"

void UStealthGameInstance::Init()
{
	Super::Init();

	// StageManager »ý¼º
	StageManager = NewObject<UStageManager>(this);
	StageManager->Initialize();
}

