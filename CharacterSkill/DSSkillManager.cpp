// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSkill/DSSkillManager.h"

#include "CharacterSkill/DSMeleeSkillComponent.h"
#include "CharacterSkill/WhirlWind.h"
#include "GameData/DSGameSingleton.h"
#include "DSSkillManager.h"

// Sets default values for this component's properties
UDSSkillManager::UDSSkillManager()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxMp = 100.f;

	static ConstructorHelpers::FObjectFinder<UBlueprint> WhirlWindRef(TEXT("/Game/DarkSorcery/Character/Skills/WhirlWind/WhirlWind.WhirlWind"));
	if (WhirlWindRef.Object)
	{
		WhirlWind = WhirlWindRef.Object;
	}

	bWantsInitializeComponent = true;

	for(int i = 0; i < 3; i++)
	{
		QuickSkills.Add(FQuickSlotSkill());
		QuickSkillName.Add(FName(""));
	}
}

void UDSSkillManager::InitializeComponent()
{
	SetMp(MaxMp);
	NowMp = MaxMp;
}

// Called every frame
void UDSSkillManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (SkillActor)
	{
		SkillActor->SetActorLocation(GetOwner()->GetActorLocation());
	}

	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("Slot[1] Skill Name : %s | Use Mana : %.0f"), *QuickSkills[1].SkillName.ToString(), QuickSkills[1].Mana));
}

void UDSSkillManager::SetMp(float NewMp)
{
	NowMp -= NewMp;
	OnMpChanged.Broadcast(NowMp);
}

void UDSSkillManager::ActivateSkill(FVector PlayerLocation, FRotator PlayerRotation, int SkillNum)
{
	FName SkillName = QuickSkillName[SkillNum];
	ADSCharacterSkill* Skill = GetWorld()->SpawnActor<ADSCharacterSkill>(ADSCharacterSkill::StaticClass(), PlayerLocation, PlayerRotation);
	// DSMeleeSkillComponent need To Follow the Character (Ex. WhirlWind)
	//AWhirlWind *Skill = GetWorld()->SpawnActor<AWhirlWind>(AWhirlWind::StaticClass(), PlayerLocation, PlayerRotation);
	if (Skill)
	{
		UDSCharacterSkillComponent* SkillComponent = Cast<UDSCharacterSkillComponent>(Skill->GetComponentByClass(UDSCharacterSkillComponent::StaticClass()));
		//UDSMeleeSkillComponent *SkillComponent = Cast<UDSMeleeSkillComponent>(Skill->GetComponentByClass(UDSMeleeSkillComponent::StaticClass()));
		if (SkillComponent)
		{
			SkillActor = Skill;
			SkillActor->OnDestroyed.AddDynamic(this, &UDSSkillManager::DeActivateSkill);
		}
	}
}

void UDSSkillManager::DeActivateSkill(AActor *DestroySkill)
{
	SkillActor = nullptr;
}

void UDSSkillManager::AddQuickSlot(FName NewSkillName, int SlotNum)
{
	QuickSkillName[SlotNum] = NewSkillName;

	FDSCharacterSkillData Skill = UDSGameSingleton::Get().GetCharacterSkillData(NewSkillName);
	FQuickSlotSkill SettingSkill(NewSkillName, Skill.Mana, Skill.Damage, Skill.CoolTime);
	QuickSkills[SlotNum] = SettingSkill;
	
}

void UDSSkillManager::RemoveQuickSlot(int SlotNum)
{
	QuickSkillName[SlotNum] = "";

	QuickSkills[SlotNum] = FQuickSlotSkill();
	
}
