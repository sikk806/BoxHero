// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DSAnimNotify_WeaponCollision.h"
#include "Interface/DSWeaponCollisionInterface.h"
#include "DSAnimNotify_WeaponCollision.h"

void UDSAnimNotify_WeaponCollision::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation, const FAnimNotifyEventReference &EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);
    
    if(MeshComp)
    {
        IDSWeaponCollisionInterface* WeaponCollision = Cast<IDSWeaponCollisionInterface>(MeshComp->GetOwner());
        if(WeaponCollision)
        {
            WeaponCollision->SettingWeaponCollision();
        }
    }
}