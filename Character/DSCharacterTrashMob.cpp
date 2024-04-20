// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DSCharacterTrashMob.h"
#include "Character/DSCharacterPlayer.h"

#include "AI/DSTrashMobAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "DSCharacterTrashMob.h"

ADSCharacterTrashMob::ADSCharacterTrashMob()
{
    // Character Skeletal Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/DarkSorcery/Enemy/TrashMob/SK_CharM_Forge.SK_CharM_Forge"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

    // Anim Instance (Anim Blueprint)
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/DarkSorcery/Enemy/TrashMob/Animation/ADS_TrashMob.ADS_TrashMob_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackRef(TEXT("/Script/Engine.AnimMontage'/Game/DarkSorcery/Enemy/TrashMob/Animation/AM_AttackTrashMob.AM_AttackTrashMob'"));
	if(AttackRef.Object)
	{
		AttackMontage = AttackRef.Object;
	}

	SkeletalMeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
    SkeletalMeshWeapon->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponRef(TEXT("/Script/Engine.SkeletalMesh'/Game/DarkSorcery/Enemy/TrashMob/Weapon/Hammer/SK_Forging_ForgeHammer02.SK_Forging_ForgeHammer02'"));
	if(WeaponRef.Object)
	{
		SkeletalMeshWeapon->SetSkeletalMesh(WeaponRef.Object);
	}

	WeaponBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponBoxCollision->SetupAttachment(SkeletalMeshWeapon);
	WeaponBoxCollision->SetRelativeScale3D(FVector(1.f, 1.f, 2.f));
    WeaponBoxCollision->SetRelativeLocation(FVector(0.f, 0.f, 63.f));
	WeaponBoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    //GetMesh()->SetHiddenInGame(true);
    AIControllerClass = ADSTrashMobAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ADSCharacterTrashMob::BeginPlay()
{
	Super::BeginPlay();

	// WeaponHitCheckBinding
    WeaponBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ADSCharacterTrashMob::CallOnHitDelegate);
}

float ADSCharacterTrashMob::GetAIPatrolRadius()
{
    return 500.0f;
}

float ADSCharacterTrashMob::GetAIDetectedRange()
{
    return 1000.0f;
}

float ADSCharacterTrashMob::GetAIAttackRange()
{
    return 200.0f;
}

float ADSCharacterTrashMob::GetAITurnSpeed()
{
    return 0.0f;
}

void ADSCharacterTrashMob::SetAttackDelegate(const FAICharacterAttackFinished &InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

// Have to coding the ProgressComboCommand()
void ADSCharacterTrashMob::AttackByAI()
{
	AttackBegin();
}

void ADSCharacterTrashMob::AttackBegin()
{
	const float AttackSpeedRate = 0.7f;
    UAnimInstance *AttackInstance = GetMesh()->GetAnimInstance();

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

    if(AttackInstance)
    {
        AttackInstance->Montage_Play(AttackMontage, AttackSpeedRate);
    }

	FOnMontageEnded EndDelegate;
    EndDelegate.BindUObject(this, &ADSCharacterTrashMob::AttackEnd);
    AttackInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);

}

void ADSCharacterTrashMob::AttackEnd(UAnimMontage *TargetMontage, bool IsProperlyEnded)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	
	NotifyActionEnd();
}

void ADSCharacterTrashMob::NotifyActionEnd()
{
	OnAttackFinished.ExecuteIfBound();
}

// can cause problems if you are hit while attacking and the montage is interrupted.
void ADSCharacterTrashMob::SettingWeaponCollision()
{
    if (WeaponBoxCollision->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
    {
        WeaponBoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
    else
    {
        WeaponBoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}
void ADSCharacterTrashMob::CallOnHitDelegate(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	ADSCharacterPlayer *HitActor = Cast<ADSCharacterPlayer>(OtherActor);
    if (HitActor)
    {
        FHitResult &HitResult = const_cast<FHitResult &>(SweepResult);
        if (&HitResult)
        {
            OnHit.Broadcast(HitActor, HitResult);
        }
    }
}