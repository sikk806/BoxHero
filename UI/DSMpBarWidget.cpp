// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DSMpBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

UDSMpBarWidget::UDSMpBarWidget(const FObjectInitializer &ObjectInitializer)
{
    MaxMp = -1.f;
}

void UDSMpBarWidget::NativeConstruct()
{
    Super::NativeConstruct();

    MpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PbMpBar")));
    ensure(MpProgressBar);
    
    MpInfo = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtMpInfo")));
    //ensure(HpInfo);

    IDSCharacterWidgetInterface* CharacterWidget = Cast<IDSCharacterWidgetInterface>(OwningActor);
    if(CharacterWidget)
    {
        CharacterWidget->SetCharacterWidget(this);
    }
}

void UDSMpBarWidget::UpdateMpBar(float NewCurrentMp)
{
    ensure(MaxMp > 0.f);
    if(MpProgressBar)
    {
        MpProgressBar->SetPercent(NewCurrentMp / MaxMp);
    }
    if(MpInfo)
    {
        int iCurrentMp = FMath::CeilToInt(NewCurrentMp);
        int iMaxMp = FMath::CeilToInt(MaxMp);

        FString ManaInfo = FString::Printf(TEXT("%d / %d"), iCurrentMp, iMaxMp);
        
        FText ManaText = FText::FromString(ManaInfo);
        MpInfo->SetText(ManaText);
    }
}
