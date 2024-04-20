// Fill out your copyright notice in the Description page of Project Settings.

#include "GameData/DSGameSingleton.h"

DEFINE_LOG_CATEGORY(LogDSGameSingleton);

UDSGameSingleton::UDSGameSingleton()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/DarkSorcery/GameData/DST_CharacterSkillData.DST_CharacterSkillData'"));
    if (DataTableRef.Object)
    {
        const UDataTable *DataTable = DataTableRef.Object;
        check(DataTable->GetRowMap().Num() > 0);

        TArray<uint8 *> ValueArray;
        DataTable->GetRowMap().GenerateValueArray(ValueArray);

        TArray<FName> KeyArray;
        DataTable->GetRowMap().GenerateKeyArray(KeyArray);

        TArray<TPair<FName, uint8*>> PairArray;
        for(int i = 0; i < KeyArray.Num(); i++)
        {
            TPair<FName, uint8*> Zipped(KeyArray[i], ValueArray[i]);
            PairArray.Add(Zipped);
        }

        Algo::Transform(PairArray, CharacterSkillTable,
                        [](TPair<FName, uint8*> MakePair)
                        {
                            return TPair<FName, FDSCharacterSkillData>(MakePair.Key, *reinterpret_cast<FDSCharacterSkillData*>(MakePair.Value));
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
