#pragma once

#include "CoreMinimal.h"
#include "CharacterSkill/DSCharacterSkill.h"
#include "MonsterSkill/RightHandAttack.h"

class DSMonsterSkillFactory {
public:
    static ADSCharacterSkill* CreateSkill(UWorld* World, FName SkillName, const FVector& PlayerLocation, const FRotator& PlayerRotation)
    {
        if(SkillName == FName(TEXT("RightHandAttack")))
        {
            return World->SpawnActor<ARightHandAttack>(ARightHandAttack::StaticClass(), PlayerLocation, PlayerRotation);
        }

        return nullptr;
    }
};