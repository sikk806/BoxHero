// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterSkill/DSMidBossSkillManager.h"
#include "MonsterSkill/DSMonsterSkillFactory.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "DSMidBossSkillManager.h"

UDSMidBossSkillManager::UDSMidBossSkillManager()
{
    // 0. RightHandAttack
    MonsterSkillSet.Add(FSkillAttackInfo(0, FName("RightHandAttack"), 1000.f));
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
    if (NextSkillName == "RightHandAttack")
    {
        CopySkill(NextSkillName, MonsterLocation, MonsterRotation, 4);
    }
    else
    {
        ADSCharacterSkill *Skill = DSMonsterSkillFactory::CreateSkill(GetWorld(), NextSkillName, MonsterLocation, MonsterRotation);
        SkillActor = Skill;
    }
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Check")));
    SkillActor->OnDestroyed.AddDynamic(this, &UDSMidBossSkillManager::DeActivateSkill);
}

void UDSMidBossSkillManager::DeActivateSkill(AActor *DestroySkill)
{
    SkillActor = nullptr;
}

void UDSMidBossSkillManager::CopySkill(FName SkillName, FVector MonsterLocation, FRotator MonsterRotation, int Copies)
{
    if (SkillName == "RightHandAttack")
    {
        for (int i = 0; i < Copies; i++)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Check ; %d"), i));
            FVector NewLocation = MonsterLocation + FVector(i * 100.f, 0.f, 0.f);
            FRotator NewRotaion = MonsterRotation + FRotator(0.f, -i * 30.f + 10.f, 0.f);
            ADSCharacterSkill *Skill = DSMonsterSkillFactory::CreateSkill(GetWorld(), SkillName, NewLocation, NewRotaion);
            ACharacter *Character = Cast<ACharacter>(GetOwner());
            if (Character)
            {
                GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Check")));
                Skill->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("RightHandAttack"));
                Skill->SetActorRelativeLocation(FVector(0.f, 0.f, 0.f));
                Skill->SetActorRelativeRotation(FRotator(0.f, 0.f, 0.f));
            }

            SkillActor = Skill;
        }
    }
}
