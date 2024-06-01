// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterSkill/RightHandAttack.h"
#include "MonsterSkill/RightHandAttackComponent.h"
#include "MonsterSkill/RightHandAttackSceneComponent.h"
#include "Character/DSCharacterPlayer.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "Engine/DamageEvents.h"

ARightHandAttack::ARightHandAttack()
{
    //PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("SkillMovement"));
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("AttackBoundary"));
    SphereComponent->SetupAttachment(RootComponent);
    SphereComponent->SetSphereRadius(2.f);
    SphereComponent->bHiddenInGame = false;
    SphereComponent->SetNotifyRigidBodyCollision(true);

    RightHandAttackActorComponent = CreateDefaultSubobject<URightHandAttackComponent>(TEXT("RightHandAttackComponent"));
    RightHandAttackSceneComponent = CreateDefaultSubobject<URightHandAttackSceneComponent>(TEXT("RightHandAttackEffect"));

    RightHandAttackSceneComponent->SetupAttachment(RootComponent);

    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARightHandAttack::ActivateCollision);

    // Init ProjectileMovement
    ProjectileMovement->SetUpdatedComponent(RootComponent);
    ProjectileMovement->InitialSpeed = 0.f;
    ProjectileMovement->MaxSpeed = 800.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->ProjectileGravityScale = 0.f;
}

void ARightHandAttack::BeginPlay()
{
    Super::BeginPlay();
    // Throw Check With Montage
    SetActorScale3D(FVector(10.f, 10.f, 10.f));

    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Check BeginPlay")));

    GetWorldTimerManager().SetTimer(ThrowTimer, this, &ARightHandAttack::Detach, 1.1f, false);
    GetWorldTimerManager().SetTimer(DestroyTimer, this, &ARightHandAttack::DestroyActor, 4.f, false);
}

void ARightHandAttack::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ARightHandAttack::SetSkillSpeed(float Speed)
{
    ProjectileMovement->MaxSpeed = Speed;
}

void ARightHandAttack::Detach()
{
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    FVector LaunchDirection = GetActorForwardVector() * 1000;
    ProjectileMovement->Velocity = LaunchDirection;
    ProjectileMovement->Activate();
}

void ARightHandAttack::ActivateCollision(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (OtherActor)
    {
        ADSCharacterPlayer *CharacterPlayer = Cast<ADSCharacterPlayer>(OtherActor);
        if (CharacterPlayer)
        {
            FDamageEvent DamageEvent;
            CharacterPlayer->TakeDamage(RightHandAttackActorComponent->Damage, DamageEvent, GetInstigatorController(), this);

            GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Damage")));

            Destroy();
        }
    }
}
