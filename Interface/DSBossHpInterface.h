// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DSBossHpInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDSBossHpInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
// Add this which the enemy is not TrashMob.
// Have to Visible the HpBar at Main Character HUD Enemy Hpbar.
class DARKSORCERY_API IDSBossHpInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
