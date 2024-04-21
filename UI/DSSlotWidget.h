// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DSUserWidget.h"
#include "DSSlotWidget.generated.h"

/**
 *
 */
UENUM(BlueprintType)
enum ESlotType
{
	SLOT_None UMETA(DisplayName = "None"),
	SLOT_Skill UMETA(DisplayName = "Skill"),
	SLOT_Item UMETA(DisplayName = "Item"),
	SLOT_QuickSkill UMETA(DisplayName = "QuickSkill"),
	SLOT_QuickItem UMETA(DisplayName = "QuickItem"),
};

UCLASS()
class DARKSORCERY_API UDSSlotWidget : public UDSUserWidget
{
	GENERATED_BODY()

public:
	UDSSlotWidget(const FObjectInitializer &ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int SlotNum;
};
