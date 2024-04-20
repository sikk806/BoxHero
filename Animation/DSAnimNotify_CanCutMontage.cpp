// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DSAnimNotify_CanCutMontage.h"
#include "Interface/DSCutMontageInterface.h"
#include "DSAnimNotify_CanCutMontage.h"

void UDSAnimNotify_CanCutMontage::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if(MeshComp)
    {
        IDSCutMontageInterface* CutMontage = Cast<IDSCutMontageInterface>(MeshComp->GetOwner());
        if(CutMontage)
        {
            CutMontage->CutAttackMontage();
        }
    }
}