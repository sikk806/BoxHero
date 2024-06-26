// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSkill/WhirlWind.h"
#include "CharacterSkill/WhirlWindComponent.h"
#include "CharacterSkill/WhirlWindSceneComponent.h"
#include "Character/DSCharacterEnemy.h"
#include "Character/DSCharacterNamed.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "TimerManager.h"
#include "Engine/DamageEvents.h"

// Sets default values
AWhirlWind::AWhirlWind()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	WhirlWindActorComponent = CreateDefaultSubobject<UWhirlWindComponent>(TEXT("WhirlWindComponent"));
	WhirlWindSceneComponent = CreateDefaultSubobject<UWhirlWindSceneComponent>(TEXT("WhirlWindEffect"));

	WhirlWindSceneComponent->SetupAttachment(RootComponent);

	CheckTime = 0.f;
	UseMana = WhirlWindActorComponent->Mana;
}

// Called when the game starts or when spawned
void AWhirlWind::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DestroyTimer, this, &AWhirlWind::DestroyActor, 2.24f);
}

// Called every frame
void AWhirlWind::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckTime += DeltaTime;
	if (CheckTime > 0.25f)
	{
		CheckTime = 0.f;
		TArray<FHitResult> OutHitResult;
		FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);

		bool HitDetected = GetWorld()->SweepMultiByChannel(OutHitResult, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(Radius), Params);
		if (HitDetected)
		{
			for (const FHitResult &Hit : OutHitResult)
			{
				AActor *HitActor = Hit.GetActor();
				if (HitActor)
				{
					ADSCharacterEnemy *Enemy = Cast<ADSCharacterEnemy>(HitActor);
					if (Enemy)
					{
						FDamageEvent DamageEvent;
						ADSCharacterNamed *Named = Cast<ADSCharacterNamed>(Enemy);
						if (Named)
						{
							Named->TakeDamage(WhirlWindActorComponent->Damage, DamageEvent, OwnerController, this);
						}
						else
						{
							Enemy->TakeDamage(WhirlWindActorComponent->Damage, DamageEvent, OwnerController, this);
						}
					}
				}
			}
			// #if ENABLE_DRAW_DEBUG

			// 			FColor DrawColor = HitDetected ? FColor::Green : FColor::Red;

			// 			DrawDebugCapsule(GetWorld(), GetActorLocation(), 125.f, Radius, FRotationMatrix::MakeFromZ(OutHitResult.ImpactNormal).ToQuat(), DrawColor, false, 5.f);

			// #endif
		}
	}
}
