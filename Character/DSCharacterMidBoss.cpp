// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/DSCharacterMidBoss.h"
#include "MonsterSkill/DSMidBossSkillManager.h"
#include "AI/DSMidBossAIController.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DSCharacterMidBoss.h"

ADSCharacterMidBoss::ADSCharacterMidBoss()
{
	// Movement
	GetCharacterMovement()->MaxWalkSpeed = 800.f;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(100.f, 250.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// Mesh Setting
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -675.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetRelativeScale3D(FVector(5.f, 5.f, 5.f));

	// Character Skeletal Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DarkSorcery/Enemy/MidBoss/Mesh/SK_Ancient_Golem.SK_Ancient_Golem'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	SkeletalMeshDrill = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Drill"));
	SkeletalMeshDrill->SetupAttachment(GetMesh(), TEXT("Drill"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DrillRef(TEXT("/Game/DarkSorcery/Enemy/MidBoss/Mesh/SK_Ancient_Golem_Moving_Wheels.SK_Ancient_Golem_Moving_Wheels"));
	if (DrillRef.Object)
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
	if (RingRef.Object)
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

	SkillManager = CreateDefaultSubobject<UDSMidBossSkillManager>(TEXT("SkillManager"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SkillRef(TEXT("/Script/Engine.AnimMontage'/Game/DarkSorcery/Enemy/MidBoss/Animation/AM_MidBossAttack.AM_MidBossAttack'"));
	if(SkillRef.Object)
	{
		SkillMontage = SkillRef.Object;
	}

	AIControllerClass = ADSMidBossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIAttackRange = 0.f;

	EnemyName = TEXT("Ancient Golem");
}

void ADSCharacterMidBoss::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMeshDrill->Play(true);
	SkeletalMeshRing->Play(true);

	AIAttackRange = SkillManager->GetNextSkillRange();
}

void ADSCharacterMidBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UAnimInstance *AnimInstance = GetMesh()->GetAnimInstance();

	if(AnimInstance->GetCurrentActiveMontage())
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Montage Name : %f"), AnimInstance->Montage_GetPosition(AnimInstance->GetCurrentActiveMontage())));
}

float ADSCharacterMidBoss::GetAIPatrolRadius()
{
	return 5000.0f;
}

float ADSCharacterMidBoss::GetAIDetectedRange()
{
	return 6000.0f;
}

float ADSCharacterMidBoss::GetAIAttackRange()
{
	return AIAttackRange;
}

float ADSCharacterMidBoss::GetAITurnSpeed()
{
	return 0.0f;
}

void ADSCharacterMidBoss::SetAttackDelegate(const FAICharacterAttackFinished &InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void ADSCharacterMidBoss::AttackByAI()
{
	AttackBegin();
}
void ADSCharacterMidBoss::AttackBegin()
{
	float AttackSpeedRate = 1.f;
	SkillManager->ActivateSkill(GetActorLocation(), GetActorRotation());

	UAnimInstance *AttackInstance = GetMesh()->GetAnimInstance();
	if(AttackInstance)
	{
		AttackInstance->Montage_Play(SkillMontage, AttackSpeedRate);
		AttackInstance->Montage_JumpToSection(SkillManager->GetNextSkillName(), SkillMontage);
	}

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ADSCharacterMidBoss::AttackEnd);
	AttackInstance->Montage_SetEndDelegate(EndDelegate, SkillMontage);

	SkillManager->SettingNextSkill();
	AIAttackRange = SkillManager->GetNextSkillRange();
}

void ADSCharacterMidBoss::AttackEnd(UAnimMontage *TargetMontage, bool IsProperlyEnded)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("AttackEnd")));

	NotifyActionEnd();
}

void ADSCharacterMidBoss::NotifyActionEnd()
{
	OnAttackFinished.ExecuteIfBound();
}

void ADSCharacterMidBoss::CastDelay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Enter Cast Delay")));
	UAnimInstance *AnimInstance = GetMesh()->GetAnimInstance();
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Montage Name : %s"), *AnimInstance->GetCurrentActiveMontage()->GetName()));
	if(AnimInstance)
	{
		AnimInstance->Montage_Pause(SkillMontage);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Pause Montage: ")));
		GetWorld()->GetTimerManager().SetTimer(CastTimer, this, &ADSCharacterMidBoss::ResumeMontage, 3.f, false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("No Playing Montage")));
	}
}

void ADSCharacterMidBoss::ResumeMontage()
{
	UAnimInstance *AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance)
	{
		AnimInstance->Montage_Resume(AnimInstance->GetCurrentActiveMontage());
	}
}
