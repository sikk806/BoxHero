// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterSkill/DSMidBossSkillManager.h"
#include "MonsterSkill/DSMonsterSkillFactory.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UDSMidBossSkillManager::UDSMidBossSkillManager()
{
    // 0. RightHandAttack
    MonsterSkillSet.Add(FSkillAttackInfo(0, FName("RightHandAttack"), 650.f));
}

void UDSMidBossSkillManager::BeginPlay()
{
    SettingNextSkill();
}

void UDSMidBossSkillManager::SettingNextSkill()
{
    int32 RandomSkillNumber = FMath::RandRange(0, MonsterSkillSet.Num() - 1);
    NextSkillName = MonsterSkillSet[RandomSkillNumber].SkillName;
    NextSkillRange = MonsterSkillSet[RandomSkillNumber].AttackRangeWithRadius;
}

void UDSMidBossSkillManager::ActivateSkill(FVector MonsterLocation, FRotator MonsterRotation)
{
    ADSCharacterSkill *Skill = DSMonsterSkillFactory::CreateSkill(GetWorld(), NextSkillName, MonsterLocation, MonsterRotation);
    if (Skill)
    {
        if (NextSkillName == "RightHandAttack")
        {
            ACharacter *Character = Cast<ACharacter>(GetOwner());
            if (Character)
            {
                GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Check")));
                Skill->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("RightHandAttack"));
                Skill->SetActorRelativeLocation(FVector(0.f, 0.f, 0.f));
                Skill->SetActorRelativeRotation(FRotator(0.f, 0.f, 0.f));
            }
        }
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Check")));
        SkillActor = Skill;
        SkillActor->OnDestroyed.AddDynamic(this, &UDSMidBossSkillManager::DeActivateSkill);
    }
}

void UDSMidBossSkillManager::DeActivateSkill(AActor *DestroySkill)
{
    SkillActor = nullptr;
}
