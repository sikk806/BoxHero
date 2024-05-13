// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_CanAttack.h"
#include "AI/DSAI.h"
#include "AIController.h"
#include "Interface/DSEnemyAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
    NodeName = TEXT("CanAttack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if(!ControllingPawn)
    {
        return false;
    }

    IDSEnemyAIInterface* AIPawn = Cast<IDSEnemyAIInterface>(ControllingPawn);
    if(!AIPawn)
    {
        return false;
    }

    APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
    if(!Target)
    {
        return false;
    }

    float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
    float AttackRangeWithRadius = AIPawn->GetAIAttackRange();
    bResult = (DistanceToTarget <= AttackRangeWithRadius);

    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("D2T : %f, Distance : %f, bResult : %d"), DistanceToTarget, AttackRangeWithRadius, bResult));

    return bResult;
}
