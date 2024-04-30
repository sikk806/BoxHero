// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSCharacterSkill.h"
#include "Parrying.generated.h"

/**
 *
 */
UCLASS()
class DARKSORCERY_API AParrying : public ADSCharacterSkill
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AParrying();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent *SceneComponent;

	// Skill Option
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParryingComponent> Parrying;
};
