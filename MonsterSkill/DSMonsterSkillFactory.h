#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSCharacterSkill.h"
#include "MonsterSkill/RightHandAttack.h"

class DSSkillFactory {
public:
    static ADSCharacterSkill* CreateSkill(UWorld* World, FName SkillName, const FVector& PlayerLocation, const FRotator& PlayerRotation)
    {
        if(SkillName == FName(TEXT("RightHandAttack")))
        {
            return World->SpawnActor<AWhirlWind>(AWhirlWind::StaticClass(), PlayerLocation, PlayerRotation);
        }

        return nullptr;
    }
};