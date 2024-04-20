// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DSCharacterSkillData.h"
#include "DSGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDSGameSingleton, Error, All);
/**
 *
 */
UCLASS()
class DARKSORCERY_API UDSGameSingleton : public UObject
{
	GENERATED_BODY()

public:
	UDSGameSingleton();
	static UDSGameSingleton &Get();

	// Character Skill Data Section
public:
	FORCEINLINE TPair<FName, FDSCharacterSkillData> GetCharacterSkillData(int32 SkillNo) const { return CharacterSkillTable.IsValidIndex(SkillNo) ? CharacterSkillTable[SkillNo] : TPair<FName, FDSCharacterSkillData>(); }
	//FORCEINLINE FDSCharacterSkillData GetCharacterSkillData(FName SkillName) const { return CharacterSkillTable.Contains(SkillName) ? CharacterSkillTable[SkillName] : FDSCharacterSkillData(); }
	
	UPROPERTY()
	int32 TotalCharacterSkills;

private:
	TArray<TPair<FName, FDSCharacterSkillData>> CharacterSkillTable;
};
