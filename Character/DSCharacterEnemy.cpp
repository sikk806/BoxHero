// Fill out your copyright notice in the Description page of Project Settings.

#include "DSCharacterEnemy.h"
#include "AI/DSEnemyAIController.h"

ADSCharacterEnemy::ADSCharacterEnemy()
{
}

void ADSCharacterEnemy::AttackBegin()
{
    
}

void ADSCharacterEnemy::AttackEnd(UAnimMontage *TargetMontage, bool IsProperlyEnded)
{
}

void ADSCharacterEnemy::SetAttackCheckTimer()
{
}

void ADSCharacterEnemy::SetDead()
{
    Super::SetDead();

    ADSEnemyAIController* EnemyAIController = Cast<ADSEnemyAIController>(GetController());
    if(EnemyAIController)
    {
        EnemyAIController->StopAI();
    }
}