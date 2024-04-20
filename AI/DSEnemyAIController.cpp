// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DSEnemyAIController.h"
#include "DSAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ADSEnemyAIController::ADSEnemyAIController()
{
    
}

void ADSEnemyAIController::RunAI()
{
    UBlackboardComponent* BlackboardPtr = Blackboard.Get();
    if(UseBlackboard(BBAsset, BlackboardPtr))
    {
        Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());

        bool RunResult = RunBehaviorTree(BTAsset);
        if(RunResult)
        ensure(RunResult);
    }

}

void ADSEnemyAIController::StopAI()
{
    UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if(BTComponent)
    {
        BTComponent->StopTree();
    }
}

void ADSEnemyAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    RunAI();
}