// Fill out your copyright notice in the Description page of Project Settings.

#include "GameData/DSGameSingleton.h"

DEFINE_LOG_CATEGORY(LogDSGameSingleton);

UDSGameSingleton::UDSGameSingleton()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/DarkSorcery/GameData/DST_CharacterSkillData.DST_CharacterSkillData'"));
    if (DataTableRef.Object)
    {
        const UDataTable *DataTable = DataTableRef.Object;
        //check(DataTable->GetRowMap().Num() > 0);

        const TMap<FName, uint8 *> &ValueMap = DataTable->GetRowMap();

        Algo::Transform(ValueMap, CharacterSkillTable,
                        [](const TPair<FName, uint8 *> &Pair)
                        {
                            return TPair<FName, FDSCharacterSkillData>(Pair.Key, *reinterpret_cast<FDSCharacterSkillData *>(Pair.Value));
                        });
    }

    TotalCharacterSkills = CharacterSkillTable.Num();
    ensure(TotalCharacterSkills > 0);
}

UDSGameSingleton &UDSGameSingleton::Get()
{
    UDSGameSingleton *Singleton = Cast<UDSGameSingleton>(GEngine->GameSingleton);
    if (Singleton)
    {
        return *Singleton;
    }

    UE_LOG(LogDSGameSingleton, Error, TEXT("Invalid UDSGameSingleton"));

    return *NewObject<UDSGameSingleton>();
}
