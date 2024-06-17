// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DSEnemyHpBar.h"
#include "UI/DSHpBarWidget.h"
#include "DSEnemyHpBar.h"
#include "Components/TextBlock.h"



UDSEnemyHpBar::UDSEnemyHpBar(const FObjectInitializer &ObjectInitializer)
{
    MaxHp = -1.f;
}

void UDSEnemyHpBar::NativeConstruct()
{
    Super::NativeConstruct();

    EnemyHpWidget = Cast<UDSHpBarWidget>(GetWidgetFromName(TEXT("HpBar")));
    ensure(EnemyHpWidget);

    EnemyName = Cast<UTextBlock>(GetWidgetFromName(TEXT("EnemyName")));
    ensure(EnemyName);

    EnemyHpText = Cast<UTextBlock>(GetWidgetFromName(TEXT("EnemyHpText")));
    ensure(EnemyHpText);
}

void UDSEnemyHpBar::SetMaxHp(float NewMaxHp)
{
    EnemyHpWidget->SetMaxHp(NewMaxHp);
    MaxHp = NewMaxHp;
}

void UDSEnemyHpBar::UpdateHpBar(float NewCurrentHp)
{
    EnemyHpWidget->UpdateHpBar(NewCurrentHp);
    NowHp = NewCurrentHp;

}

void UDSEnemyHpBar::SetEnemyText(FName Name)
{
    EnemyName->SetText(FText::FromName(Name));
    FString HpInfo = FString::SanitizeFloat(MaxHp, 0);
    HpInfo += " / ";
    HpInfo += FString::SanitizeFloat(NowHp, 0);
    EnemyHpText->SetText(FText::FromString(HpInfo));
}
