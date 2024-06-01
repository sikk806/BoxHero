// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DSCharacterNamed.h"
#include "Interface/DSCharacterHUDInterface.h"
#include "UI/DSHUDWidget.h"
#include "DSCharacterNamed.h"

ADSCharacterNamed::ADSCharacterNamed()
{

}

float ADSCharacterNamed::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    IDSCharacterHUDInterface* Main = Cast<IDSCharacterHUDInterface>(EventInstigator->GetPawn());
    if(Main)
    {
        UDSHUDWidget* MainHUD = Cast<UDSHUDWidget>(Main->GetHUDWidget());
        if(MainHUD)
        {
            MainHUD->SetEnemyMaxHp(Stat->GetMaxHp());
            MainHUD->UpdateEnemyHp(Stat->GetNowHp());
            MainHUD->SetEnemyName(EnemyName);
            MainHUD->SetEnemyHpBarVisibility();
        }
    }
    return DamageAmount;
}
