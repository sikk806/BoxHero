// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyState_MotionWarping.h"
#include "DSAnimNotify_ComboWarping.generated.h"

/**
 * 
 */
UCLASS()
class DARKSORCERY_API UDSAnimNotify_ComboWarping : public UAnimNotifyState_MotionWarping
{
	GENERATED_BODY()

protected:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	
};
