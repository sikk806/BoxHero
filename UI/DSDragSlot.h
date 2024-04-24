// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DSDragSlot.generated.h"

enum ESlotType;

/**
 * 
 */
UCLASS()
class DARKSORCERY_API UDSDragSlot : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	FName SlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ESlotType> SlotType;
	
};
