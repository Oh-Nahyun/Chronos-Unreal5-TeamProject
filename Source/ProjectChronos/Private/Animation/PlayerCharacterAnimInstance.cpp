// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacterAnimInstance.h"

//#include "GameFramework/Character.h"
#include "Character/CPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UPlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningPlayerCharacter = Cast<ACPlayerCharacter>(TryGetPawnOwner());

	if (OwningPlayerCharacter)
	{
		PlayerCharacterMovementComponent = OwningPlayerCharacter->GetCharacterMovement();
	}
}

void UPlayerCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningPlayerCharacter || !PlayerCharacterMovementComponent)
		return;

	Velocity = OwningPlayerCharacter->GetVelocity();

	GroundSpeed = Velocity.Size2D();

	bHasAcceleration = PlayerCharacterMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	bIsFalling = PlayerCharacterMovementComponent->IsFalling();

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(Velocity, OwningPlayerCharacter->GetActorRotation());

	StateType = OwningPlayerCharacter->GetStateType();

	CurrentWeaponType = OwningPlayerCharacter->CurrentWeaponType;
}
