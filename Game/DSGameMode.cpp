// Fill out your copyright notice in the Description page of Project Settings.

#include "DSGameMode.h"

#include "Player/DSPlayerController.h"

ADSGameMode::ADSGameMode()
{
    static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/DarkSorcery.DSCharacterPlayer"));
    // Default Pawn Class
    if(DefaultPawnClassRef.Class)
    {
        DefaultPawnClass = DefaultPawnClassRef.Class;
    }

    static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/DarkSorcery.DSPlayerController"));
    if(PlayerControllerClassRef.Class)
    {
        PlayerControllerClass = PlayerControllerClassRef.Class;
    }
}