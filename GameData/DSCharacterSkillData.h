
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DSCharacterSkillData.generated.h"

USTRUCT(BlueprintType)
struct FDSCharacterSkillData : public FTableRowBase
{
    GENERATED_BODY();

public:
    //Mana : ManaCost, Stamina : StaminaCost, Damage, HitCount : how many times attack, CoolTime, Description
    FDSCharacterSkillData() : Mana(0.f), Stamina(0.f), Damage(0.f), HitCount(0), CoolTime(0.f), Description(FText::FromString(TEXT(""))) {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
    float Mana;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
    float Stamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
    int32 HitCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
    float CoolTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
    FText Description;



};