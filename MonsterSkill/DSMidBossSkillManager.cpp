// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterSkill/DSMidBossSkillManager.h"

#include "BehaviorTree/BlackboardComponent.h"

UDSMidBossSkillManager::UDSMidBossSkillManager()
{
    // 0. RightHandAttack
    MonsterSkillSet.Add(FSkillAttackInfo(0, FName("RightHandAttack"), 650.f));
    MonsterSkillSet.Add(FSkillAttackInfo(1, FName("LeftHandAttack"), 450.f));
}

void UDSMidBossSkillManager::BeginPlay()
{
    SettingNextSkill();
}

void UDSMidBossSkillManager::SettingNextSkill()
{
    int32 RandomSkillNumber = FMath::RandRange(0, MonsterSkillSet.Num()-1);
    NextSkillName = MonsterSkillSet[RandomSkillNumber].SkillName;
    NextSkillRange = MonsterSkillSet[RandomSkillNumber].AttackRangeWithRadius;
}
