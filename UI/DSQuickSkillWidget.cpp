// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DSQuickSkillWidget.h"
#include "UI/DSSlotWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Character/DSCharacterPlayer.h"
#include "DSQuickSkillWidget.h"

#include "Framework/Application/SlateApplication.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UDSQuickSkillWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    QuickSkills.Reserve(3);
    QuickSkills.Add(FName(""));
    QuickSkills.Add(FName(""));
    QuickSkills.Add(FName(""));
}

void UDSQuickSkillWidget::Init(ADSCharacterPlayer *NewPlayer)
{
    bIsFocusable = true;
    if(NewPlayer)
    {
        SetOwningPlayer(NewPlayer);
        MainSkillManager = NewPlayer->GetSkillManager();
    }
    TArray<UWidget *> GetWidget;
    if (!WidgetTree)
    {
        UE_LOG(LogTemp, Warning, TEXT("Widget Tree is null!"));
    }
    else
    {
        WidgetTree->GetAllWidgets(GetWidget);

        for (auto widget : GetWidget)
        {
            UDSSlotWidget *SetSlot = Cast<UDSSlotWidget>(widget);
            if (!SetSlot)
                continue;
            if(OwningPlayer)
            {
                SetSlot->SetOwningPlayer(OwningPlayer);
            }
            SetSlot->SetSlotType(ESlotType::SLOT_QuickSkill);
            SetSlot->SetParentWidget(this);
            SetSlot->SetSlotData();
        }
    }

}

void UDSQuickSkillWidget::AddQuickSlot(FName NewSkillName, int SkillNum)
{
    QuickSkills[SkillNum] = NewSkillName;
    IDSQuickSlotUpdateInterface* QuickSlot = Cast<IDSQuickSlotUpdateInterface>(MainSkillManager);
    if(QuickSlot)
    {
        QuickSlot->AddQuickSlot(NewSkillName, SkillNum);
    }
}

void UDSQuickSkillWidget::RemoveQuickSlot(int SkillNum)
{
    QuickSkills[SkillNum] = FName("");
    IDSQuickSlotUpdateInterface* QuickSlot = Cast<IDSQuickSlotUpdateInterface>(MainSkillManager);
    if(QuickSlot)
    {
        QuickSlot->RemoveQuickSlot(SkillNum);
    }
}
