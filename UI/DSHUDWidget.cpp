// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DSHUDWidget.h"
#include "Interface/DSCharacterHUDInterface.h"
#include "UI/DSHpBarWidget.h"
#include "UI/DSMpBarWidget.h"
#include "UI/DSSlotWidget.h"
#include "UI/DSSkillWidget.h"
#include "DSHUDWidget.h"

UDSHUDWidget::UDSHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
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

    IDSCharacterHUDInterface* HUDPawn = Cast<IDSCharacterHUDInterface>(GetOwningPlayerPawn());
    if(HUDPawn)
    {
        HUDPawn->SetupHUDWidget(this);
    }

}

void UDSHUDWidget::SettingHUD(float SetMaxHp, float SetMaxMp)
{
    MaxHp = SetMaxHp;
    MaxMp = SetMaxMp;
    HpBar->SetMaxHp(MaxHp);
    MpBar->SetMaxMp(MaxMp);
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
