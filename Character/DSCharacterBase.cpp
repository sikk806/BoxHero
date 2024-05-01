// Fill out your copyright notice in the Description page of Project Settings.

#include "DSCharacterBase.h"
#include "CharacterStat/DSCharacterStatComponent.h"

#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UI/DSWidgetComponent.h"
#include "UI/DSHpBarWidget.h"

// Sets default values
ADSCharacterBase::ADSCharacterBase()
{
	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -100.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));

	// Dead Montage
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/DarkSorcery/Animation/AM_Dead.AM_Dead'"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}

	// Stat Component
	Stat = CreateDefaultSubobject<UDSCharacterStatComponent>(TEXT("Stat"));

	// Particle
	DamagedParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DamagedParticle"));
	DamagedParticle->SetupAttachment(RootComponent);

	// Widget
	HpBar = CreateDefaultSubobject<UDSWidgetComponent>(TEXT("Widget"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));

	static ConstructorHelpers::FClassFinder<UUserWidget> HpBarRef(TEXT("/Game/DarkSorcery/UI/WBP_HpBar.WBP_HpBar_C"));
	if (HpBarRef.Class)
	{
		HpBar->SetWidgetClass(HpBarRef.Class);
		HpBar->SetWidgetSpace(EWidgetSpace::Screen);
		HpBar->SetDrawSize(FVector2D(150.f, 15.f));
		HpBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ADSCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Stat->OnHpZero.AddUObject(this, &ADSCharacterBase::SetDead);
	OnHit.AddUObject(this, &ADSCharacterBase::AttackCheck);
}

// Called when the game starts or when spawned
void ADSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADSCharacterBase::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADSCharacterBase::AttackCheck(AActor *OtherActor, FHitResult &HitResult)
{
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

	const float AttackDamage = 10.f;

	FDamageEvent DamageEvent;
	HitResult.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
}

float ADSCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Stat->ApplyDamage(DamageAmount);

	return DamageAmount;
}

// Have an Animation Error When PlayerDead.
void ADSCharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadMontage();

	SetActorEnableCollision(false);

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([&]()
																						 { Destroy(); }),
										   3.f, false);
}

void ADSCharacterBase::PlayDeadMontage()
{
	UAnimInstance *AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->StopAllMontages(0.0f);
		AnimInstance->Montage_Play(DeadMontage, 1.f);
	}
}

bool ADSCharacterBase::IsMontagePlaying(UAnimMontage *AnimMontage)
{
	UAnimInstance *AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		return AnimInstance->Montage_IsPlaying(AnimMontage);
	}
	return false;
}

void ADSCharacterBase::PauseMontage()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Pause Montage"));
	UAnimInstance *AnimInstance = GetMesh()->GetAnimInstance();
	UAnimMontage *MontageInstance = AnimInstance->GetCurrentActiveMontage();
	AnimInstance->Montage_Pause(MontageInstance);

	FTimerHandle ResumeMontageTimer;
	GetWorld()->GetTimerManager().SetTimer(ResumeMontageTimer, FTimerDelegate::CreateLambda([AnimInstance, MontageInstance]()
																							{ GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Pause Montage"));
																								AnimInstance->Montage_Resume(MontageInstance); }),
										   2.f, false);
}

void ADSCharacterBase::CastDelay()
{
	EMovementMode EMM = GetCharacterMovement()->MovementMode;
	if (EMM == EMovementMode::MOVE_Walking)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	}
	else if (EMM == EMovementMode::MOVE_None)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void ADSCharacterBase::SetCharacterWidget(UDSUserWidget *InUserWidget)
{
	UDSHpBarWidget *HpBarWidget = Cast<UDSHpBarWidget>(InUserWidget);
	if (HpBarWidget)
	{
		HpBarWidget->SetMaxHp(Stat->GetMaxHp());
		HpBarWidget->UpdateHpBar(Stat->GetNowHp());
		Stat->OnHpChanged.AddUObject(HpBarWidget, &UDSHpBarWidget::UpdateHpBar);
	}
}
