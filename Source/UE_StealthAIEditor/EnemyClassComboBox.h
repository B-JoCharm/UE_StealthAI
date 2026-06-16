// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "EnemyCharacter.h"
#include "EnemyClassComboBox.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyClassSelected, TSubclassOf<AEnemyCharacter>, SelectedClass);

UCLASS(BlueprintType, Blueprintable)
class UE_STEALTHAIEDITOR_API UEnemyClassComboBox : public UUserWidget
{
    GENERATED_BODY()

public:
    // StageDataAsset의 AvailableEnemyClasses 배열을 받아서 드롭다운 항목 채우기
    UFUNCTION(BlueprintCallable, Category = "EnemyClassComboBox")
    void SetEnemyClasses(const TArray<TSubclassOf<AEnemyCharacter>>& InClasses);

    // 현재 선택된 Enemy 클래스 반환
    UFUNCTION(BlueprintCallable, Category = "EnemyClassComboBox")
    TSubclassOf<AEnemyCharacter> GetSelectedClass() const;

    // 선택된 클래스가 바뀔 때 호출되는 델리게이트
    UPROPERTY(BlueprintAssignable, Category = "EnemyClassComboBox")
    FOnEnemyClassSelected OnEnemyClassSelected;

protected:
    virtual void NativeConstruct() override;

    // UMG ComboBoxString 위젯 (BP 디자인 탭에서 연결)
    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UComboBoxString* ComboBox;

private:
    // Enemy 클래스 목록
    TArray<TSubclassOf<AEnemyCharacter>> EnemyClasses;

    // 현재 선택된 인덱스
    int32 SelectedIndex = 0;

    // ComboBox 선택 변경 시 호출
    UFUNCTION()
    void OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
};