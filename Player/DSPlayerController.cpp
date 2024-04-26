// Fill out your copyright notice in the Description page of Project Settings.

#include "DSPlayerController.h"
#include "Character/DSCharacterPlayer.h"
#include "UI/DSHUDWidget.h"

ADSPlayerController::ADSPlayerController()
{
    static ConstructorHelpers::FClassFinder<UDSHUDWidget> HUDWidgetClassRef(TEXT("/Game/DarkSorcery/UI/WBP_DSHUD.WBP_DSHUD_C"));
    if (HUDWidgetClassRef.Class)
    {
        DSHUDWidgetClass = HUDWidgetClassRef.Class;
    }
}

void ADSPlayerController::BeginPlay()
{
    Super::BeginPlay();

    FInputModeGameOnly GameOnlyInputMode;
    SetInputMode(GameOnlyInputMode);

    bEnableMouseOverEvents = true;

    if (DSHUDWidgetClass)
    {
        DSHUDWidget = CreateWidget<UDSHUDWidget>(this, DSHUDWidgetClass);
        if (DSHUDWidget)
        {
            ADSCharacterPlayer* NewPlayer = Cast<ADSCharacterPlayer>(GetPawn());
            if(NewPlayer)
            {
                DSHUDWidget->SetPlayer(NewPlayer);
            }
            DSHUDWidget->AddToViewport();
        }
    }
}