// Fill out your copyright notice in the Description page of Project Settings.

#include "DSCharacterPlayer.h"
#include "Player/DSPlayerController.h"
#include "Character/DSComboActionData.h"
#include "CharacterSkill/DSSkillManager.h"
#include "Character/DSCharacterEnemy.h"
#include "CharacterStat/DSCharacterStatComponent.h"
#include "GameData/DSGameSingleton.h"
#include "UI/DSHUDWidget.h"
#include "UI/DSMpBarWidget.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "MotionWarpingComponent.h"
#include "Particles/ParticleSystemComponent.h"

ADSCharacterPlayer::ADSCharacterPlayer()
{
    // Debug
    GetCapsuleComponent()->bHiddenInGame = false;

    // Camera
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 1000.f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    // Character Skeletal Mesh
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/DarkSorcery/Character/Mesh/SK_CharM_Cardboard.SK_CharM_Cardboard"));
    if (CharacterMeshRef.Object)
    {
        GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
    }

    // Input Mapping
    static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/DarkSorcery/Input/IMC_Default.IMC_Default'"));
    if (InputMappingContextRef.Object)
    {
        DefaultMappingContext = InputMappingContextRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/DarkSorcery/Input/Actions/IA_Jump.IA_Jump'"));
    if (InputActionJumpRef.Object)
    {
        JumpAction = InputActionJumpRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/DarkSorcery/Input/Actions/IA_Move.IA_Move'"));
    if (InputActionMoveRef.Object)
    {
        MoveAction = InputActionMoveRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/DarkSorcery/Input/Actions/IA_Look.IA_Look'"));
    if (InputActionLookRef.Object)
    {
        LookAction = InputActionLookRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/DarkSorcery/Input/Actions/IA_Attack.IA_Attack'"));
    if (InputActionAttackRef.Object)
    {
        AttackAction = InputActionAttackRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputActionSkillRef(TEXT("/Script/EnhancedInput.InputAction'/Game/DarkSorcery/Input/Actions/IA_UseSkill.IA_UseSkill'"));
    if (InputActionSkillRef.Object)
    {
        SkillAction = InputActionSkillRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UInputAction> InputSkillWidgetRef(TEXT("/Script/EnhancedInput.InputAction'/Game/DarkSorcery/Input/Actions/IA_Skills.IA_Skills'"));
    if (InputSkillWidgetRef.Object)
    {
        SkillWidget = InputSkillWidgetRef.Object;
    }

    // Anim Instance (Anim Blueprint)
    static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/DarkSorcery/Animation/ADS_Character.ADS_Character_C"));
    if (AnimInstanceClassRef.Class)
    {
        GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
    }

    Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
    Weapon->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));
    Weapon->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

    // Weapon Static Mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponRef(TEXT("/Script/Engine.StaticMesh'/Game/DarkSorcery/Character/Weapon/Cardboard_Buster_Sword.Cardboard_Buster_Sword'"));
    if (WeaponRef.Object)
    {
        Weapon->SetStaticMesh(WeaponRef.Object);
    }
    Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    WeaponBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBoxCollision"));
    WeaponBoxCollision->SetupAttachment(Weapon);
    WeaponBoxCollision->SetRelativeScale3D(FVector(0.25f, 0.5f, 2.25f));
    WeaponBoxCollision->SetRelativeLocation(FVector(0.f, 0.f, 90.f));
    WeaponBoxCollision->bHiddenInGame = false;

    // Attack Section
    static ConstructorHelpers::FObjectFinder<UDSComboActionData> ComboActionDataRef(TEXT("/Script/DarkSorcery.DSComboActionData'/Game/DarkSorcery/GameData/DSA_ComboAttack.DSA_ComboAttack'"));
    if (ComboActionDataRef.Object)
    {
        ComboActionData = ComboActionDataRef.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboAttackRef(TEXT("/Script/Engine.AnimMontage'/Game/DarkSorcery/Animation_Sword/AM_AttackCombo.AM_AttackCombo'"));
    if (ComboAttackRef.Object)
    {
        ComboAttackMontage = ComboAttackRef.Object;
    }

    // Skill Section
    SkillManager = CreateDefaultSubobject<UDSSkillManager>(TEXT("SkillManager"));

    static ConstructorHelpers::FObjectFinder<UAnimMontage> SkillRef(TEXT("/Script/Engine.AnimMontage'/Game/DarkSorcery/Animation_Sword/Skill/AM_SkillMontage.AM_SkillMontage'"));
    if (SkillRef.Object)
    {
        SkillMontage = SkillRef.Object;
    }

    // Anim Section
    MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
    bWarp = false;

    // Particle Section
    static ConstructorHelpers::FObjectFinder<UParticleSystem> WeaponParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/DarkSorcery/Character/Effects/Attack/P_Skill_Leap_Base_Charge_Weapon.P_Skill_Leap_Base_Charge_Weapon'"));
    if (WeaponParticleRef.Object)
    {
        WeaponParticle = WeaponParticleRef.Object;
    }

    // UI Section
    bWidgetOn = false;
}

void ADSCharacterPlayer::BeginPlay()
{
    Super::BeginPlay();

    APlayerController *PlayerController = CastChecked<APlayerController>(GetController());
    if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(DefaultMappingContext, 0);
    }

    WeaponCollisionDisabled();

    // WeaponHitCheckBinding
    WeaponBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ADSCharacterPlayer::CallOnHitDelegate);
}

void ADSCharacterPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::Move);
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::Look);
    EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::Attack);
    EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::ActivateSkill);
    EnhancedInputComponent->BindAction(SkillWidget, ETriggerEvent::Triggered, this, &ADSCharacterPlayer::CharacterSkillWidget);
}

// Tick For Debug
void ADSCharacterPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADSCharacterPlayer::Move(const FInputActionValue &Value)
{
    if (!bWidgetOn)
    {
        if (IsMontagePlaying(ComboAttackMontage) && bCutAttackMontage)
        {
            bCutAttackMontage = false;
            UAnimInstance *AnimInstance = GetMesh()->GetAnimInstance();
            if (AnimInstance)
            {
                AnimInstance->Montage_Stop(0.25f, ComboAttackMontage);
            }
        }
        FVector2D MovementVector = Value.Get<FVector2D>();

        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.X);
        AddMovementInput(RightDirection, MovementVector.Y);
    }
}

void ADSCharacterPlayer::Look(const FInputActionValue &Value)
{
    if (!bWidgetOn)
    {
        FVector2D LookAxisVector = Value.Get<FVector2D>();

        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void ADSCharacterPlayer::Attack()
{
    if (!bWidgetOn)
    {
        ProcessComboCommand();
    }
}

void ADSCharacterPlayer::CallOnHitDelegate(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    ADSCharacterEnemy *HitActor = Cast<ADSCharacterEnemy>(OtherActor);
    if (HitActor)
    {
        FHitResult &HitResult = const_cast<FHitResult &>(SweepResult);
        if (&HitResult)
        {
            OnHit.Broadcast(HitActor, HitResult);
            HitActor->DamagedParticle->SetTemplate(WeaponParticle);
            HitActor->DamagedParticle->SetActive(true);
        }
    }
}

void ADSCharacterPlayer::ProcessComboCommand()
{
    if (CurrentCombo == 0)
    {
        ComboAttackBegin();
        return;
    }

    if (!ComboTimerHandle.IsValid())
    {
        HasNextComboCommand = false;
    }
    else
    {
        HasNextComboCommand = true;
    }
}

void ADSCharacterPlayer::CutAttackMontage()
{
    bCutAttackMontage = true;
}

void ADSCharacterPlayer::ComboAttackBegin()
{
    // Need Count Of Combo Attack
    CurrentCombo = 1;

    // Movement Setting
    // GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

    // Animation Setting
    const float AttackSpeedRate = 1.f;
    UAnimInstance *AttackInstance = GetMesh()->GetAnimInstance();

    if (AttackInstance)
    {
        AttackInstance->Montage_PlayWithBlendIn(ComboAttackMontage, 0.05f, AttackSpeedRate);
    }

    FOnMontageEnded EndDelegate;
    EndDelegate.BindUObject(this, &ADSCharacterPlayer::AttackEnd);
    AttackInstance->Montage_SetEndDelegate(EndDelegate, ComboAttackMontage);

    ComboTimerHandle.Invalidate();
    SetComboCheckTimer();
}

void ADSCharacterPlayer::AttackEnd(UAnimMontage *TargetMontage, bool IsProperlyEnded)
{
    ensure(CurrentCombo != 0);
    bCutAttackMontage = false;
    CurrentCombo = 0;
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
    bWarp = false;
}

void ADSCharacterPlayer::SetComboCheckTimer()
{
    int32 ComboIndex = CurrentCombo - 1;
    ensure(ComboActionData->EffectiveFrameCount.IsValidIndex(ComboIndex));

    const float AttackSpeedRate = 1.f;
    float ComboEffectiveTime = (ComboActionData->EffectiveFrameCount[ComboIndex] / ComboActionData->FrameRate) / AttackSpeedRate;

    if (ComboEffectiveTime > 0.f)
    {
        GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ADSCharacterPlayer::ComboCheck, ComboEffectiveTime, false);
    }
}

void ADSCharacterPlayer::ComboCheck()
{
    ComboTimerHandle.Invalidate();
    if (HasNextComboCommand)
    {
        bWarp = false;
        UAnimInstance *AnimInstance = GetMesh()->GetAnimInstance();

        CurrentCombo = FMath::Clamp(CurrentCombo + 1, 1, ComboActionData->MaxComboCount);
        FName NextSection = *FString::Printf(TEXT("%s%d"), *ComboActionData->MontageSectionNamePrefix, CurrentCombo);
        AnimInstance->Montage_JumpToSection(NextSection, ComboAttackMontage);
        SetComboCheckTimer();
        HasNextComboCommand = false;
    }
}

void ADSCharacterPlayer::SettingWeaponCollision()
{
    if (WeaponBoxCollision->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
    {
        WeaponBoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
    else
    {
        WeaponBoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

void ADSCharacterPlayer::ActivateSkill()
{
    ADSPlayerController *PlayerController = Cast<ADSPlayerController>(Controller);
    FKey PressedKey;
    if (PlayerController)
    {
        PressedKey = PlayerController->GetLastKeyPressed();
    }
    int SkillNum = -1;
    if (PressedKey.ToString() == "Q")
    {
        SkillNum = 0;
    }
    else if (PressedKey.ToString() == "E")
    {
        SkillNum = 1;
    }
    else if (PressedKey.ToString() == "R")
    {
        SkillNum = 2;
    }

    FName SkillName = SkillManager->GetActivateSkillName(SkillNum);
    FQuickSlotSkill Skill = SkillManager->GetActivateSkill(SkillNum);
    if (SkillName != "")
    {
        float UseMana = Skill.Mana;
        if (UseMana != 0.f && SkillManager->GetNowMp() >= UseMana)
        {
            SkillManager->SetMp(UseMana);
            SkillManager->ActivateSkill(GetActorLocation(), GetActorRotation(), SkillNum);
            UAnimInstance *AnimInstance = GetMesh()->GetAnimInstance();
            if (AnimInstance && SkillMontage)
            {
                AnimInstance->Montage_Play(SkillMontage, 1.f);
                AnimInstance->Montage_JumpToSection(SkillName, SkillMontage);
            }
        }
    }
    // GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, FString::Printf(TEXT("Last Key Pressed: %s"), *PressedKey.ToString()));
}

void ADSCharacterPlayer::SetComboWarping()
{
    if (!bWarp)
    {
        UAnimInstance *AnimInstance = GetMesh()->GetAnimInstance();
        if (AnimInstance)
        {
            FName CurrentMontageSection = AnimInstance->Montage_GetCurrentSection();

            float WarpDistance = 0;
            FString SectionNameString = "Combo" + FString::FromInt(CurrentCombo);
            FName SectionName = *SectionNameString;
            if (CurrentMontageSection == SectionName)
                WarpDistance = ComboActionData->WarpDistance[CurrentCombo - 1];
            ActorForwardVector = GetActorForwardVector();
            PlayerLocation = GetActorLocation();
            TargetLocation = (ActorForwardVector.GetSafeNormal() * WarpDistance) + PlayerLocation;
            TargetRotator = UKismetMathLibrary::MakeRotFromX(ActorForwardVector);

            bWarp = true;
        }
    }

    if (MotionWarpingComponent)
    {
        MotionWarpingComponent->AddOrUpdateWarpTargetFromLocationAndRotation(TEXT("Warp"), TargetLocation, TargetRotator);
    }
}

UActorComponent *ADSCharacterPlayer::GetSkillManager()
{
    UActorComponent *ActorComponent = Cast<UActorComponent>(SkillManager);
    if (SkillManager)
    {
        return SkillManager;
    }
    else
    {
        return nullptr;
    }
}

void ADSCharacterPlayer::SetCharacterWidget(UDSUserWidget *InUserWidget)
{
    Super::SetCharacterWidget(InUserWidget);

    UDSMpBarWidget *MpBarWidget = Cast<UDSMpBarWidget>(InUserWidget);
    if (MpBarWidget)
    {
        MpBarWidget->SetMaxMp(SkillManager->GetMaxMp());
        MpBarWidget->UpdateMpBar(SkillManager->GetNowMp());
    }
}

void ADSCharacterPlayer::SetupHUDWidget(UDSHUDWidget *InHUDWidget)
{
    if (InHUDWidget)
    {
        InHUDWidget->SettingHUD(Stat->GetMaxHp(), SkillManager->GetMaxMp());
        InHUDWidget->UpdateHpBar(Stat->GetNowHp());
        InHUDWidget->UpdateMpBar(SkillManager->GetNowMp());
        HUDWidget = InHUDWidget;

        Stat->OnHpChanged.AddUObject(InHUDWidget, &UDSHUDWidget::UpdateHpBar);
        SkillManager->OnMpChanged.AddUObject(InHUDWidget, &UDSHUDWidget::UpdateMpBar);
    }
}

void ADSCharacterPlayer::SetQuickSlotInfo()
{
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Success To Connect QuickSlot And Player!"));
}

void ADSCharacterPlayer::CharacterSkillWidget()
{
    if (HUDWidget)
    {
        bWidgetOn = HUDWidget->SetSkillWidgetVisibility();
    }
}
