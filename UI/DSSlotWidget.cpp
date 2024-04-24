// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DSSlotWidget.h"
#include "GameData/DSGameSingleton.h"

#include "Framework/Application/SlateApplication.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DSSlotWidget.h"

UDSSlotWidget::UDSSlotWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{

}

void UDSSlotWidget::NativeConstruct()
{
    Super::NativeConstruct();

    SlotOverlay = Cast<UOverlay>(GetWidgetFromName("OLSlot"));
    ensure(SlotOverlay);

	Thumbnail = Cast<UImage>(GetWidgetFromName("ImgThumbnail"));
    ensure(Thumbnail);

    SlotInfo = Cast<UTextBlock>(GetWidgetFromName("TxtSlot"));
    ensure(SlotInfo);

}

void UDSSlotWidget::NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

    UE_LOG(LogTemp, Warning, TEXT("Drag"));
}

void UDSSlotWidget::SetSlotData()
{
    switch(SlotType)
    {
        case ESlotType::SLOT_Skill:
        {
            ensure(!SlotName.IsNone());
            FDSCharacterSkillData SlotData = UDSGameSingleton::Get().GetCharacterSkillData(SlotName);
            SlotInfo->SetVisibility(ESlateVisibility::Hidden);
            SetThumbnail(SlotData.Thumbnail);
            

            break;
        }
        default:
         break;
    }
}

void UDSSlotWidget::SetSlotType(ESlotType Type)
{
    SlotType = Type;
}

void UDSSlotWidget::SetThumbnail(FText ThumbnailLink)
{
    UTexture2D* ThumbnailTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ThumbnailLink.ToString()));
    Thumbnail->SetBrushFromTexture(ThumbnailTexture);
}

void UDSSlotWidget::SetText(FText TextSlotInfo)
{
    SlotInfo->SetText(TextSlotInfo);
}

FReply UDSSlotWidget::NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
    FEventReply Reply;
    Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    if(InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true)
    {
        // RightMousebutton
    }
    else if(InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
    {
        switch(SlotType)
        {
            case SLOT_Skill : 
            {
                Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
                
            }
        }
    }


    return Reply.NativeReply;
}
