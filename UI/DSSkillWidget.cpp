// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/DSSkillWidget.h"
#include "UI/DSSlotWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Character/DSCharacterPlayer.h"

void UDSSkillWidget::NativeConstruct()
{
    // TArray<UWidget *> GetWidget;
    // if (!WidgetTree)
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("Widget Tree is null!"));
    // }
    // else
    // {
    //     WidgetTree->GetAllWidgets(GetWidget);

    //     for (auto widget : GetWidget)
    //     {
    //         UDSSlotWidget *SetSlot = Cast<UDSSlotWidget>(widget);
    //         if (!SetSlot)
    //             continue;

    //         SetSlot->SetSlotType(ESlotType::SLOT_Skill);
    //         SetSlot->SetSlotData();
    //         break;
    //     }
    // }
}

void UDSSkillWidget::Init(ADSCharacterPlayer* NewPlayer)
{
    if(NewPlayer)
    {
        SetOwningPlayer(NewPlayer);
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
            SetSlot->SetSlotType(ESlotType::SLOT_Skill);
            SetSlot->SetSlotData();
            break;
        }
    }
}
