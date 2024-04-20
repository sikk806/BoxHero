// Fill out your copyright notice in the Description page of Project Settings.

#include "DSAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UDSAnimInstance::UDSAnimInstance()
{
    MovingThreshold = 2.f;
    JumpingThreshold = 100.f;
}

void UDSAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    Owner = Cast<ACharacter>(GetOwningActor());
    if (Owner)
    {
        Movement = Owner->GetCharacterMovement();
    }
}

void UDSAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (Movement)
    {
        Velocity = Movement->Velocity;
        MovementSpeed = Velocity.Size2D();
        bIsIdle = (MovementSpeed < MovingThreshold);
        bIsFalling = Movement->IsFalling();
        bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshold);
    }
}
