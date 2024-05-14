// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "AI/DSAI.h"
#include "AIController.h"
#include "Interface/DSEnemyAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Attack::UBTTask_Attack()
{

}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
    if(!ControllingPawn)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Fail ControllingPawn")));
        return EBTNodeResult::Failed;
    }

    IDSEnemyAIInterface* AIPawn = Cast<IDSEnemyAIInterface>(ControllingPawn);
    if(!AIPawn)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Fail AIPawn")));
        return EBTNodeResult::Failed;
    }

    FAICharacterAttackFinished OnAttackDelegate;
    OnAttackDelegate.BindLambda(
        [&]()
        {
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        }
    );

    AIPawn->SetAttackDelegate(OnAttackDelegate);

    AIPawn->AttackByAI();
    
    return EBTNodeResult::InProgress;
}
