// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DSAnimNotify_CastDelay.h"
#include "Interface/DSCastDelayInterface.h"

void UDSAnimNotify_CastDelay::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if(MeshComp)
    {
        IDSCastDelayInterface* SkillCastDelay = Cast<IDSCastDelayInterface>(MeshComp->GetOwner());
        if(SkillCastDelay)
        {
            SkillCastDelay->CastDelay();
        }
    }
}