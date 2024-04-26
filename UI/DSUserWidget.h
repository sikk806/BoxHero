// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/DSCharacterPlayer.h"
#include "DSUserWidget.generated.h"

UCLASS()
class DARKSORCERY_API UDSUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetOwningActor(AActor *NewOwner) { OwningActor = NewOwner; }
	FORCEINLINE void SetOwningPlayer(ADSCharacterPlayer* NewPlayer) { OwningPlayer = NewPlayer; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Actor)
	TObjectPtr<AActor> OwningActor;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Actor)
	TObjectPtr<ADSCharacterPlayer> OwningPlayer;

};
