// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DSTrashMobAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ADSTrashMobAIController::ADSTrashMobAIController()
{
    const ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/DarkSorcery/Enemy/TrashMob/AI/BB_TrashMob.BB_TrashMob'"));
    if(BBAssetRef.Object)
    {
        BBAsset = BBAssetRef.Object;
    }

    const ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/DarkSorcery/Enemy/TrashMob/AI/BT_TrashMob.BT_TrashMob'"));
    if(BTAssetRef.Object)
    {
        BTAsset = BTAssetRef.Object;
    }
}
void ADSTrashMobAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
}