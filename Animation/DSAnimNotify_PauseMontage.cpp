// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DSAnimNotify_PauseMontage.h"
#include "Interface/DSPauseMontageInterface.h"

void UDSAnimNotify_PauseMontage::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    
    if(MeshComp)
    {
        IDSPauseMontageInterface* PauseMontage = Cast<IDSPauseMontageInterface>(MeshComp->GetOwner());
        if(PauseMontage)
        {
            PauseMontage->PauseMontage();
        }
    }
}