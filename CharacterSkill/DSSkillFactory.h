#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSCharacterSkill.h"
#include "CharacterSkill/WhirlWind.h"
#include "CharacterSkill/Parrying.h"

class DSSkillFactory {
public:
    static ADSCharacterSkill* CreateSkill(UWorld* World, FName SkillName, const FVector& PlayerLocation, const FRotator& PlayerRotation)
    {
        if(SkillName == FName(TEXT("WhirlWind")))
        {
            return World->SpawnActor<AWhirlWind>(AWhirlWind::StaticClass(), PlayerLocation, PlayerRotation);
        }
        else if(SkillName == FName(TEXT("Parrying")))
        {
            return World->SpawnActor<AParrying>(AParrying::StaticClass(), PlayerLocation, PlayerRotation);
        }

        return nullptr;
    }
};