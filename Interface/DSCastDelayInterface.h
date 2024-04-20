// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DSCastDelayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDSCastDelayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DARKSORCERY_API IDSCastDelayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void CastDelay() = 0;
};
