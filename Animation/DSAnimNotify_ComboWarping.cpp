// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DSAnimNotify_ComboWarping.h"
#include "Interface/DSComboWarpingInterface.h"
#include "DSAnimNotify_ComboWarping.h"

void UDSAnimNotify_ComboWarping::NotifyTick(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, float FrameDeltaTime, const FAnimNotifyEventReference &EventReference)
{
    Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

    if(MeshComp)
    {
        IDSComboWarpingInterface* ComboWarping = Cast<IDSComboWarpingInterface>(MeshComp->GetOwner());

        if(ComboWarping)
        {
            ComboWarping->SetComboWarping();
        }
    }
}