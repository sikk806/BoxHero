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

void ADSPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    FInputKeyBinding QB(FInputChord(EKeys::Q), EInputEvent::IE_Pressed);
    QB.bConsumeInput = true;
    QB.KeyDelegate.GetDelegateForManualSet().BindUObject(this, &ADSPlayerController::HandleKeyPress, EKeys::Q);

    FInputKeyBinding EB(FInputChord(EKeys::E), EInputEvent::IE_Pressed);
    EB.bConsumeInput = true;
    EB.KeyDelegate.GetDelegateForManualSet().BindUObject(this, &ADSPlayerController::HandleKeyPress, EKeys::E);

    FInputKeyBinding RB(FInputChord(EKeys::R), EInputEvent::IE_Pressed);
    RB.bConsumeInput = true;
    RB.KeyDelegate.GetDelegateForManualSet().BindUObject(this, &ADSPlayerController::HandleKeyPress, EKeys::R);

    InputComponent->KeyBindings.Add(QB);
    InputComponent->KeyBindings.Add(EB);
    InputComponent->KeyBindings.Add(RB);
}

void ADSPlayerController::HandleKeyPress(FKey Key)
{
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("PressedKey: %s"), *Key.ToString()));
    LastKeyPressed = Key;
}
