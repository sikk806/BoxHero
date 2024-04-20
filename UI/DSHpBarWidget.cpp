// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DSHpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"



UDSHpBarWidget::UDSHpBarWidget(const FObjectInitializer &ObjectInitializer)
{
    MaxHp = -1.f;
}

void UDSHpBarWidget::NativeConstruct()
{
    Super::NativeConstruct();

    HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbHpBar")));
    ensure(HpProgressBar);
    
    HpInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtHpInfo")));
    //ensure(HpInfo);

    IDSCharacterWidgetInterface* CharacterWidget = Cast<IDSCharacterWidgetInterface>(OwningActor);
    if(CharacterWidget)
    {
        CharacterWidget->SetCharacterWidget(this);
    }
}

void UDSHpBarWidget::UpdateHpBar(float NewCurrentHp)
{
    ensure(MaxHp > 0.f);
    if(HpProgressBar)
    {
        HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
    }
    if(HpInfo)
    {
        int iCurrentHp = FMath::CeilToInt(NewCurrentHp);
        int iMaxHp = FMath::CeilToInt(MaxHp);

        FString HealthInfo = FString::Printf(TEXT("%d / %d"), iCurrentHp, iMaxHp);
        
        FText HealthText = FText::FromString(HealthInfo);
        HpInfo->SetText(HealthText);
    }
}
