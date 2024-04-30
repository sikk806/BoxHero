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
	void SetThumbnail();
	void SetText(FText TextSlotInfo);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FName SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int SlotNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float CoolTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ESlotType> SlotType;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UOverlay> SlotOverlay;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Thumbnail;

	UPROPERTY()
	TObjectPtr<class UTexture2D> ThumbnailTexture;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> SlotInfo;

// Drag And Drop The Slot
public:
	void SetParentWidget(UDSUserWidget* SetWidget);

protected:
	UPROPERTY()
	TSubclassOf<class UDSSlotWidget> DragVisualSlot;

	UPROPERTY()
	TObjectPtr<class UDSUserWidget> ParentWidget;

	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual void NativeOnDragDetected( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation ) override;
	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;
	virtual void NativeOnDragCancelled( const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation ) override;


};
