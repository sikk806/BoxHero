// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSkill/DSSkillManager.h"

#include "CharacterSkill/DSCharacterSkillComponent.h"
#include "CharacterSkill/DSSkillFactory.h"
#include "GameData/DSGameSingleton.h"

// Sets default values for this component's properties
UDSSkillManager::UDSSkillManager()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxMp = 100.f;

	bWantsInitializeComponent = true;

	for(int i = 0; i < 3; i++)
	{
		QuickSkills.Add(FQuickSlotSkill());
		QuickSkillName.Add(FName(""));
		QuickCoolTime.Add(0.f);
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

}

void UDSSkillManager::SetMp(float NewMp)
{
	NowMp -= NewMp;
	OnMpChanged.Broadcast(NowMp);
}

void UDSSkillManager::ActivateSkill(FVector PlayerLocation, FRotator PlayerRotation, int SkillNum)
{
	FName SkillName = QuickSkillName[SkillNum];
	ADSCharacterSkill* Skill = DSSkillFactory::CreateSkill(GetWorld(), SkillName, PlayerLocation, PlayerRotation);
	if(Skill)
	{
		SkillActor = Skill;
		SkillActor->OnDestroyed.AddDynamic(this, &UDSSkillManager::DeActivateSkill);
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
	QuickCoolTime[SlotNum] = Skill.CoolTime;
	
}

void UDSSkillManager::RemoveQuickSlot(int SlotNum)
{
	QuickSkillName[SlotNum] = "";

	QuickSkills[SlotNum] = FQuickSlotSkill();
	
}
