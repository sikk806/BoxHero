// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DSMidBossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ADSMidBossAIController::ADSMidBossAIController()
{
    const ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/DarkSorcery/Enemy/MidBoss/AI/BB_MidBoss.BB_MidBoss'"));
    if(BBAssetRef.Object)
    {
        BBAsset = BBAssetRef.Object;
    }

    const ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/DarkSorcery/Enemy/MidBoss/AI/BT_MidBoss.BT_MidBoss'"));
    if(BTAssetRef.Object)
    {
        BTAsset = BTAssetRef.Object;
    }
}

void ADSMidBossAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
}
