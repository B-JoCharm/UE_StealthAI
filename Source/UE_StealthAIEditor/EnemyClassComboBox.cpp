// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyClassComboBox.h"

void UEnemyClassComboBox::NativeConstruct()
{
    Super::NativeConstruct();

    if (ComboBox)
    {
        ComboBox->OnSelectionChanged.AddDynamic(this, &UEnemyClassComboBox::OnSelectionChanged);
    }
}

void UEnemyClassComboBox::SetEnemyClasses(const TArray<TSubclassOf<AEnemyCharacter>>& InClasses)
{
    EnemyClasses = InClasses;
    SelectedIndex = 0;

    if (!ComboBox) return;

    // 기존 항목 초기화
    ComboBox->ClearOptions();

    // 클래스 이름을 드롭다운 항목으로 추가
    for (const TSubclassOf<AEnemyCharacter>& EnemyClass : EnemyClasses)
    {
        if (EnemyClass)
        {
            ComboBox->AddOption(EnemyClass->GetName());
        }
    }

    // 첫 번째 항목 기본 선택
    if (EnemyClasses.Num() > 0)
    {
        ComboBox->SetSelectedIndex(0);
    }
}

TSubclassOf<AEnemyCharacter> UEnemyClassComboBox::GetSelectedClass() const
{
    if (EnemyClasses.IsValidIndex(SelectedIndex))
    {
        return EnemyClasses[SelectedIndex];
    }
    return nullptr;
}

void UEnemyClassComboBox::OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    // 선택된 문자열로 인덱스 찾기
    for (int32 i = 0; i < EnemyClasses.Num(); i++)
    {
        if (EnemyClasses[i] && EnemyClasses[i]->GetName() == SelectedItem)
        {
            SelectedIndex = i;
            OnEnemyClassSelected.Broadcast(EnemyClasses[i]);
            break;
        }
    }
}