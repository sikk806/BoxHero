// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DSUserWidget.h"
#include "Interface/DSQuickSlotUpdateInterface.h"
#include "DSQuickSkillWidget.generated.h"

UCLASS()
class DARKSORCERY_API UDSQuickSkillWidget : public UDSUserWidget, public IDSQuickSlotUpdateInterface
{
	GENERATED_BODY()
public:

	virtual void NativeOnInitialized() override;
	virtual void Init(ADSCharacterPlayer *NewPlayer);

protected:
	TArray<UWidget *> Slots;

// Main Character SkillManager
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillManager, Meta = (AllowPrivateAccess = "true"));
	TObjectPtr<UActorComponent> MainSkillManager;

	TArray<FName> QuickSkills;

	virtual void AddQuickSlot(FName NewSkillName, int SkillNum) override;
	virtual void RemoveQuickSlot(int SkillNum) override;
	
};
