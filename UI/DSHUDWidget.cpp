// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DSHUDWidget.h"
#include "Interface/DSCharacterHUDInterface.h"
#include "UI/DSHpBarWidget.h"
#include "UI/DSMpBarWidget.h"
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
    //ensure(MpBar);

    IDSCharacterHUDInterface* HUDPawn = Cast<IDSCharacterHUDInterface>(GetOwningPlayerPawn());
    if(HUDPawn)
    {
        HUDPawn->SetupHUDWidget(this);
    }
    ensure(MaxHp > 0);
    HpBar->SetMaxHp(MaxHp);

}

void UDSHUDWidget::SettingHUD(float SetMaxHp)
{
    MaxHp = SetMaxHp;
    HpBar->SetMaxHp(MaxHp);
}

void UDSHUDWidget::UpdateHpBar(float NewCurrentHp)
{
    HpBar->UpdateHpBar(NewCurrentHp);
}

void UDSHUDWidget::UpdateMpBar(float NewCurrentMp)
{
    MpBar->UpdateMpBar(NewCurrentMp);
}
