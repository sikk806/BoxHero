// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /* NowHp */);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DARKSORCERY_API UDSCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDSCharacterStatComponent();

protected:
	virtual void InitializeComponent() override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;

	FORCEINLINE float GetMaxHp() { return MaxHp; }
	FORCEINLINE float GetNowHp() { return NowHp;}
	float ApplyDamage(float DamageAmount);

protected:
	void SetHp(float NewHp);

	UPROPERTY(VisibleInstanceOnly, Category = Stat)
	float MaxHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float NowHp; 
		
};