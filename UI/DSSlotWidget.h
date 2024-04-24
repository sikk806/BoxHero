// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/DSUserWidget.h"
#include "GameData/DSCharacterSkillData.h"
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
	void SetSlotData();
	void SetSlotType(ESlotType Type);
	void SetThumbnail(FText ThumbnailLink);
	void SetText(FText TextSlotInfo);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FName SlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	int Count;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ESlotType> SlotType;

	UPROPERTY()
	TObjectPtr<class UOverlay> SlotOverlay;

	UPROPERTY()
	TObjectPtr<class UImage> Thumbnail;

	UPROPERTY()
	TObjectPtr<class UTextBlock> SlotInfo;

protected:
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
};
