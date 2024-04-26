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

    //bIsFocusable = false;
}

void UDSQuickSkillWidget::Init(ADSCharacterPlayer *NewPlayer)
{
    bIsFocusable = true;
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
            SetSlot->SetSlotType(ESlotType::SLOT_QuickSkill);
            SetSlot->SetSlotData();
        }
    }

}


// FReply UDSQuickSkillWidget::NativeOnPreviewKeyDown(const FGeometry &InGeometry, const FKeyEvent &InKeyEvent)
// {
//     GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("NativeOnKeyDown"));
//     FEventReply Reply;
//     Reply.NativeReply = Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
//     if(InKeyEvent.GetKey() == EKeys::Q)
//     {
//         if(OwningPlayer)
//         {
//             IDSQuickSlotInfoInterface* QuickSlot = Cast<IDSQuickSlotInfoInterface>(OwningPlayer);
//             if(QuickSlot)
//             {
//                 QuickSlot->SetQuickSlotInfo();
//             }
//             else
//             {
//                 GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No QuickSlotInterface in QuickSkillWidget"));
//             }
//         }
//         else
//         {
//             GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No OwningPlayer in QuickSkillWidget"));
//         }
//     }
    


//     return Reply.NativeReply;
// }
