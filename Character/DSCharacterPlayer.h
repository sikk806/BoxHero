// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "Character/DSCharacterBase.h"
#include "Interface/DSComboWarpingInterface.h"
#include "Interface/DSCutMontageInterface.h"
#include "Interface/DSWeaponCollisionInterface.h"
#include "Interface/DSCharacterHUDInterface.h"
#include "Interface/DSQuickSlotInfoInterface.h"
#include "InputActionValue.h"
#include "DSCharacterPlayer.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API ADSCharacterPlayer : public ADSCharacterBase, public IDSComboWarpingInterface, public IDSCutMontageInterface, public IDSWeaponCollisionInterface, public IDSCharacterHUDInterface, public IDSQuickSlotInfoInterface
{
	GENERATED_BODY()

public:
	ADSCharacterPlayer();
	FString Check = FString("Check Connecting The MainPlayer");

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// Tick For Debug
	virtual void Tick(float DeltaTime) override;

	// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UCameraComponent> FollowCamera;

	// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> SkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<class UInputAction> SkillWidget;

	void Move(const FInputActionValue &Value);
	void Look(const FInputActionValue &Value);

	// Attack Section
protected:
	void Attack();

	UFUNCTION()
	void CallOnHitDelegate(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	void ProcessComboCommand();
	virtual void CutAttackMontage() override;

	bool bCutAttackMontage = false;

	// Attack - Combo
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDSComboActionData> ComboActionData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> ComboAttackMontage;

	void ComboAttackBegin();
	void AttackEnd(UAnimMontage *TargetMontage, bool IsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

	int32 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool HasNextComboCommand = 0;

	// Attack - Collision
	FORCEINLINE void WeaponCollisionEnabled()
	{
		if (WeaponBoxCollision)
			WeaponBoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	FORCEINLINE void WeaponCollisionDisabled()
	{
		if (WeaponBoxCollision)
			WeaponBoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	virtual void SettingWeaponCollision() override;

	// Skill Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDSSkillManager> SkillManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> SkillMontage;

	void ActivateSkill();

	// Anim Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMotionWarpingComponent> MotionWarpingComponent;

	virtual void SetComboWarping() override;

	// Anim Section - Warp Setting
	bool bWarp;
	FVector ActorForwardVector;
	FVector PlayerLocation;
	FVector TargetLocation;
	FRotator TargetRotator;

	// Particle Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParticleSystem> WeaponParticle;

	// UI Section
public:
	UActorComponent* GetSkillManager();
	UDSHUDWidget* GetHUDWidget() override;
	
protected:
	UPROPERTY()
	TObjectPtr<class UDSHUDWidget> HUDWidget;

	virtual void SetCharacterWidget(class UDSUserWidget *InUserWidget) override;
	virtual void SetupHUDWidget(class UDSHUDWidget* InHUDWidget) override;
	virtual void SetQuickSlotInfo() override;

	void CharacterSkillWidget();

private:
	bool bWidgetOn;
};
