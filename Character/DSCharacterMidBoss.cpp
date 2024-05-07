// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DSCharacterMidBoss.h"

#include "GameFramework/CharacterMovementComponent.h"

ADSCharacterMidBoss::ADSCharacterMidBoss()
{
	// Movement
	GetCharacterMovement()->MaxWalkSpeed = 600.f;

    // Capsule
	GetCapsuleComponent()->InitCapsuleSize(150.f, 320.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// Mesh Setting
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -675.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));

	// Character Skeletal Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DarkSorcery/Enemy/MidBoss/Mesh/SK_Ancient_Golem.SK_Ancient_Golem'"));
	if(CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
		
	}

	SkeletalMeshDrill = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Drill"));
	SkeletalMeshDrill->SetupAttachment(GetMesh(), TEXT("Drill"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DrillRef(TEXT("/Game/DarkSorcery/Enemy/MidBoss/Mesh/SK_Ancient_Golem_Moving_Wheels.SK_Ancient_Golem_Moving_Wheels"));
	if(DrillRef.Object)
	{
		SkeletalMeshDrill->SetSkeletalMesh(DrillRef.Object);
		SkeletalMeshDrill->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> DrillAnimRef(TEXT("/Script/Engine.AnimSequence'/Game/DarkSorcery/Enemy/MidBoss/Animation/Anim_Drill.Anim_Drill'"));
    if (DrillAnimRef.Object)
    {
        SkeletalMeshDrill->SetAnimation(DrillAnimRef.Object);
    }

	SkeletalMeshRing = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Ring"));
	SkeletalMeshRing->SetupAttachment(GetMesh(), TEXT("Ring"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RingRef(TEXT("/Game/DarkSorcery/Enemy/MidBoss/Mesh/SK_Ancient_Golem_Head_Wheel.SK_Ancient_Golem_Head_Wheel"));
	if(RingRef.Object)
	{
		SkeletalMeshRing->SetSkeletalMesh(RingRef.Object);
		SkeletalMeshRing->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> RingAnimRef(TEXT("/Script/Engine.AnimSequence'/Game/DarkSorcery/Enemy/MidBoss/Animation/Anim_Ring.Anim_Ring'"));
    if (RingAnimRef.Object)
    {
        SkeletalMeshRing->SetAnimation(RingAnimRef.Object);
    }

	// Anim Instance (Anim Blueprint)
    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/DarkSorcery/Enemy/MidBoss/Animation/ADS_MidBoss.ADS_MidBoss_C"));
    if (AnimInstanceClassRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
    }

}

void ADSCharacterMidBoss::BeginPlay()
{
    Super::BeginPlay();

	SkeletalMeshDrill->Play(true);
	SkeletalMeshRing->Play(true);
}

void ADSCharacterMidBoss::Tick(float DeltaTime)
{

}

float ADSCharacterMidBoss::GetAIPatrolRadius()
{
    return 0.0f;
}

float ADSCharacterMidBoss::GetAIDetectedRange()
{
    return 0.0f;
}

float ADSCharacterMidBoss::GetAIAttackRange()
{
    return 0.0f;
}

float ADSCharacterMidBoss::GetAITurnSpeed()
{
    return 0.0f;
}

void ADSCharacterMidBoss::SetAttackDelegate(const FAICharacterAttackFinished &InOnAttackFinished)
{

}

void ADSCharacterMidBoss::AttackByAI()
{

}
