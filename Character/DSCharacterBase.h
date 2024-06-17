// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/DSCastDelayInterface.h"
#include "Interface/DSCharacterWidgetInterface.h"
#include "Interface/DSPauseMontageInterface.h"
#include "DSCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHitDelegate, AActor * /* Actor Of HittedActor */, FHitResult & /* Actor Hit Result */);


// Deleted CastDelayInterface... If it makes Error, need to ass IDSCastDelayInterface and function.
UCLASS()
class DARKSORCERY_API ADSCharacterBase : public ACharacter, public IDSCharacterWidgetInterface, public IDSPauseMontageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADSCharacterBase();

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// Stat Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDSCharacterStatComponent> Stat;

	// Action Section
public:
	FOnHitDelegate OnHit;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> WeaponBoxCollision;

	void AttackCheck(AActor *OtherActor, FHitResult &HitResult);

	// Anim Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dead, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	virtual void SetDead();
	void PlayDeadMontage();
	bool IsMontagePlaying(UAnimMontage *AnimMontage);
	virtual void PauseMontage() override;

	float DeadEventTime = 5.f;

	// Item Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Weapon;

	// Particle Section
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Particle, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParticleSystemComponent> DamagedParticle;

	// UI Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDSWidgetComponent> HpBar;

	virtual void SetCharacterWidget(class UDSUserWidget* InUserWidget) override;
};
