// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/DSSkillWidget.h"
#include "UI/DSSlotWidget.h"
#include "Blueprint/WidgetTree.h"

void UDSSkillWidget::NativeConstruct()
{
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

            // After Add the SetSlot to Slots Array. And Control them.
            SetSlot->SetOwningActor(this->OwningActor);
            SetSlot->SetSlotType(ESlotType::SLOT_Skill);
            SetSlot->SetSlotData();
            break;
        }
    }
}