// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DSWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API UDSWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void InitWidget() override;
	
};
