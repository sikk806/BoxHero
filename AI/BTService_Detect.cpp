// Fill out your copyright notice in the Description page of Project Settings.

#include "DSAI.h"
#include "AI/BTService_Detect.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/DSEnemyAIInterface.h"

UBTService_Detect::UBTService_Detect()
{
    NodeName = TEXT("Detect");
    Interval = 0.5f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn *ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (!ControllingPawn)
    {
        return;
    }

    FVector Center = ControllingPawn->GetActorLocation();
    UWorld *World = ControllingPawn->GetWorld();

    if (!World)
    {
        return;
    }

    IDSEnemyAIInterface *AIPawn = Cast<IDSEnemyAIInterface>(ControllingPawn);
    if (!AIPawn)
    {
        return;
    }

    // Detect Radius
    float DetectRadius = AIPawn->GetAIDetectedRange();
    
    TArray<FOverlapResult> OverlapResults;
    FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
    bool bResult = World->OverlapMultiByChannel(
        OverlapResults,
        Center,
        FQuat::Identity,
        ECC_Pawn,
        FCollisionShape::MakeSphere(DetectRadius),
        CollisionQueryParam);

    if (bResult)
    {
        for (auto const &OverlapResult : OverlapResults)
        {
            APawn *Pawn = Cast<APawn>(OverlapResult.GetActor());
            if (Pawn && Pawn->GetController()->IsPlayerController())
            {
                OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
                return;
            }
        }
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
}
