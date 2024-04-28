// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/DSSlotWidget.h"
#include "GameData/DSGameSingleton.h"
#include "Interface/DSQuickSlotInfoInterface.h"
#include "Interface/DSQuickSlotUpdateInterface.h"
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

}

void UDSSlotWidget::SetSlotData()
{
    switch (SlotType)
    {
    case ESlotType::SLOT_None:
        Thumbnail->SetColorAndOpacity(FLinearColor(0.7f, 0.7f, 0.7f));
        break;
    case ESlotType::SLOT_Skill:
        if (!ThumbnailTexture)
        {
            ensure(!SlotName.IsNone());
            FDSCharacterSkillData SlotData = UDSGameSingleton::Get().GetCharacterSkillData(SlotName);
            ThumbnailTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *SlotData.Thumbnail.ToString()));
            SetThumbnail();
        }
        else
        {
            SetThumbnail();
        }
        SlotInfo->SetVisibility(ESlateVisibility::Hidden);
        break;
    case ESlotType::SLOT_QuickSkill:
        if (SlotName == FName("None"))
        {
            Thumbnail->SetColorAndOpacity(FLinearColor(0.4f, 0.4f, 0.4f));
            switch (SlotNum)
            {
            case 0:
                SlotInfo->SetText(FText::FromString("Q"));
                break;
            case 1:
                SlotInfo->SetText(FText::FromString("E"));
                break;
            case 2:
                SlotInfo->SetText(FText::FromString("R"));
                break;
            default:
                SlotInfo->SetVisibility(ESlateVisibility::Hidden);
                break;
            }
        }
        else
        {
            SetThumbnail();
        }
        break;
    default:
        break;
    }
}

void UDSSlotWidget::SetSlotType(ESlotType Type)
{
    SlotType = Type;
}

void UDSSlotWidget::SetThumbnail()
{
    if (Thumbnail == nullptr)
    {
        return;
    }
    Thumbnail->SetBrushFromTexture(ThumbnailTexture);
}

void UDSSlotWidget::SetText(FText TextSlotInfo)
{
    SlotInfo->SetText(TextSlotInfo);
}

void UDSSlotWidget::SetParentWidget(UDSUserWidget* SetWidget)
{
    ParentWidget = SetWidget;
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
            Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
            break;
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

        if (DragVisualSlot && OwningPlayer)
        {
            APlayerController *Controller = Cast<APlayerController>(OwningPlayer->Controller);
            if (Controller)
            {
                UDSSlotWidget *VisualSlot = CreateWidget<UDSSlotWidget>(Controller, DragVisualSlot);
                if (VisualSlot)
                {
                    VisualSlot->SetRenderScale(FVector2D(0.5f, 0.5f));
                    VisualSlot->OwningPlayer = this->OwningPlayer;
                    VisualSlot->SlotName = this->SlotName;
                    VisualSlot->SlotType = this->SlotType;
                    VisualSlot->ThumbnailTexture = this->ThumbnailTexture;
                    VisualSlot->SlotInfo = this->SlotInfo;
                    VisualSlot->SetSlotData();

                    Drag->DefaultDragVisual = VisualSlot;
                }
            }
            else
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No Controller"));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No DragVisualSlot"));
        }
    }
}

bool UDSSlotWidget::NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
    Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
    UDSDragSlot *Drag = Cast<UDSDragSlot>(InOperation);

    if (Drag)
    {
        IDSQuickSlotUpdateInterface* QuickSlot = Cast<IDSQuickSlotUpdateInterface>(ParentWidget);
        switch (this->SlotType)
        {
        case ESlotType::SLOT_QuickSkill:
            SlotName = Drag->SlotName;
            ThumbnailTexture = Drag->SlotTexture;
            Thumbnail->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f));
            SetSlotData();

            if(QuickSlot)
            {
                QuickSlot->AddQuickSlot(this->SlotName, this->SlotNum);
            }
            break;
        default:
            break;
        }
        return true;
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Slot Change Fail..."));
        return false;
    }
}
