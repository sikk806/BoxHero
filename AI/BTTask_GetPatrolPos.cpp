// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_GetPatrolPos.h"
#include "AI/DSAI.h"
#include "AIController.h"
#include "Interface/DSEnemyAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_GetPatrolPos::UBTTask_GetPatrolPos()
{
}

EBTNodeResult::Type UBTTask_GetPatrolPos::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if(!ControllingPawn)
    {
        return EBTNodeResult::Failed;
    }

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
    if(!NavSystem)
    {
        return EBTNodeResult::Failed;
    }

    IDSEnemyAIInterface* AIPawn = Cast<IDSEnemyAIInterface>(ControllingPawn);
    if(!AIPawn)
    {
        return EBTNodeResult::Failed;
    }

    FVector OwnerPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_HOMEPOS);
    float PatrolRadius = AIPawn->GetAIPatrolRadius();
    FNavLocation NextPatrolPos;

    if(NavSystem->GetRandomPointInNavigableRadius(OwnerPosition, 500.f, NextPatrolPos))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLPOS, NextPatrolPos.Location);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
