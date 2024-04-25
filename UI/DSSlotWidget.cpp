// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/DSSlotWidget.h"
#include "GameData/DSGameSingleton.h"
#include "UI/DSDragSlot.h"

#include "Framework/Application/SlateApplication.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Overlay.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DSSlotWidget.h"

UDSSlotWidget::UDSSlotWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    static ConstructorHelpers::FClassFinder<UDSSlotWidget> DragVisualSlotRef(TEXT("/Game/DarkSorcery/UI/WBP_Slot.WBP_Slot_C"));
    if (DragVisualSlotRef.Class)
    {
        DragVisualSlot = DragVisualSlotRef.Class;
    }
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

void UDSSlotWidget::SetSlotData()
{
    switch (SlotType)
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
    ThumbnailTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ThumbnailLink.ToString()));
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

    if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) == true)
    {
        // RightMousebutton
    }
    else if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) == true)
    {
        switch (SlotType)
        {
        case SLOT_Skill:
        {
            Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
        }
        }
    }

    return Reply.NativeReply;
}

void UDSSlotWidget::NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation)
{
    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

    if (!OutOperation)
    {
        UDSDragSlot *Drag = NewObject<UDSDragSlot>();
        OutOperation = Drag;
        Drag->SlotName = this->SlotName;
        Drag->SlotTexture = this->ThumbnailTexture;
        Drag->SlotType = this->SlotType;

        if (DragVisualSlot)
        {
            if (OwningPlayer)
            {
                APlayerController *Controller = Cast<APlayerController>(OwningPlayer->Controller);
                if (Controller)
                {
                    UDSSlotWidget *VisualSlot = CreateWidget<UDSSlotWidget>(Cast<APlayerController>(OwningPlayer->Controller), DragVisualSlot);
                    if(VisualSlot)
                    {
                        VisualSlot->SetRenderScale(FVector2D(0.5f, 0.5f));
                        VisualSlot->OwningPlayer = this->OwningPlayer;
                        VisualSlot->SlotName = this->SlotName;
                        VisualSlot->SlotType = this->SlotType;
                        VisualSlot->ThumbnailTexture = this->ThumbnailTexture;
                        VisualSlot->SlotInfo = this->SlotInfo;

                        Drag->DefaultDragVisual = VisualSlot;
                        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Drag Complete"));
                    }
                }
                else
                    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No Controller"));
            }
            else
                UE_LOG(LogTemp, Warning, TEXT("NoOwningPlayer"));
            
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No DragVisualSlot"));
        }
    }
}