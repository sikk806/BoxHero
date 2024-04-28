// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/DSHUDWidget.h"
#include "Interface/DSCharacterHUDInterface.h"
#include "UI/DSHpBarWidget.h"
#include "UI/DSMpBarWidget.h"
#include "UI/DSSlotWidget.h"
#include "UI/DSSkillWidget.h"
#include "UI/DSQuickSkillWidget.h"
#include "DSHUDWidget.h"

UDSHUDWidget::UDSHUDWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    MaxHp = -1.f;
}

void UDSHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    HpBar = Cast<UDSHpBarWidget>(GetWidgetFromName(TEXT("WidgetHpBar")));
    ensure(HpBar);

    MpBar = Cast<UDSMpBarWidget>(GetWidgetFromName(TEXT("WidgetMpBar")));
    ensure(MpBar);

    Skill = Cast<UDSSkillWidget>(GetWidgetFromName(TEXT("WidgetSkill")));
    ensure(Skill);

    QuickSkill = Cast<UDSQuickSkillWidget>(GetWidgetFromName(TEXT("WidgetQuickSkill")));
    ensure(QuickSkill);

    IDSCharacterHUDInterface *HUDPawn = Cast<IDSCharacterHUDInterface>(GetOwningPlayerPawn());
    if (HUDPawn)
    {
        HUDPawn->SetupHUDWidget(this);
    }
}

void UDSHUDWidget::SettingHUD(float SetMaxHp, float SetMaxMp)
{
    MaxHp = SetMaxHp;
    HpBar->SetMaxHp(MaxHp);

    MaxMp = SetMaxMp;
    MpBar->SetMaxMp(MaxMp);

    Skill->Init(OwningPlayer);
    Skill->SetVisibility(ESlateVisibility::Hidden);

    QuickSkill->Init(OwningPlayer);
}

void UDSHUDWidget::UpdateHpBar(float NewCurrentHp)
{
    HpBar->UpdateHpBar(NewCurrentHp);
    HpBar->UpdateHpBarTxt(NewCurrentHp);
}

void UDSHUDWidget::UpdateMpBar(float NewCurrentMp)
{
    MpBar->UpdateMpBar(NewCurrentMp);
}

bool UDSHUDWidget::SetSkillWidgetVisibility()
{
    if (Skill->GetVisibility() == ESlateVisibility::Hidden)
    {
        Skill->SetVisibility(ESlateVisibility::Visible);
        if (OwningPlayer)
        {
            APlayerController *Controller = Cast<APlayerController>(OwningPlayer->Controller);
            if (Controller)
            {
                FInputModeGameAndUI UIOnlyInputMode;
                UIOnlyInputMode.SetWidgetToFocus(Skill->TakeWidget());
                Controller->SetInputMode(UIOnlyInputMode);
                Controller->bShowMouseCursor = true;
            }
        }
        return true;
    }
    else
    {
        Skill->SetVisibility(ESlateVisibility::Hidden);
        if (OwningPlayer)
        {
            APlayerController *Controller = Cast<APlayerController>(OwningPlayer->Controller);
            if (Controller)
            {
                FInputModeGameOnly GameOnlyInputMode;
                Controller->SetInputMode(GameOnlyInputMode);
                Controller->bShowMouseCursor = false;
            }
        }
        return false;
    }
}

FReply UDSHUDWidget::NativeOnPreviewKeyDown(const FGeometry &InGeometry, const FKeyEvent &InKeyEvent)
{
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("HUD?"));
    FEventReply Reply;
    Reply.NativeReply = Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
    if (InKeyEvent.GetKey() == EKeys::K)
    {
        if (OwningPlayer)
        {
            IDSQuickSlotInfoInterface *QuickSlot = Cast<IDSQuickSlotInfoInterface>(OwningPlayer);
            if (QuickSlot)
            {
                QuickSlot->SetQuickSlotInfo();
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No QuickSlotInterface in QuickSkillWidget"));
            }
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No OwningPlayer in QuickSkillWidget"));
        }
    }

    return Reply.NativeReply;
}
