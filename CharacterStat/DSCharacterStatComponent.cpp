// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/DSCharacterStatComponent.h"
#include "DSCharacterStatComponent.h"

// Sets default values for this component's properties
UDSCharacterStatComponent::UDSCharacterStatComponent()
{
	MaxHp = 5000.f;
	SetHp(MaxHp);

	bWantsInitializeComponent = true;
}

void UDSCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	NowHp = MaxHp;
}

float UDSCharacterStatComponent::ApplyDamage(float DamageAmount)
{
	const float PrevHp = NowHp;
	const float Damage = FMath::Clamp<float>(DamageAmount, 0, DamageAmount);
	SetHp(PrevHp - Damage);

	if(NowHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
	return Damage;
}

void UDSCharacterStatComponent::SetHp(float NewHp)
{
	NowHp = FMath::Clamp<float>(NewHp, 0.f, MaxHp);

	OnHpChanged.Broadcast(NowHp);
}
