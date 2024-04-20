// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API ADSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADSPlayerController();

protected:
	virtual void BeginPlay() override;

// HUD Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD) 
	TSubclassOf<class UDSHUDWidget> DSHUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
	TObjectPtr<class UDSHUDWidget> DSHUDWidget;
	
};
