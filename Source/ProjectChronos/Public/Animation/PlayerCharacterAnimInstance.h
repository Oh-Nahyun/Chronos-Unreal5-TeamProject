// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Other/Enums.h"
#include "PlayerCharacterAnimInstance.generated.h"

class ACharacter;
class UCharacterMovementComponent;
class ACPlayerCharacter;

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UPlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACPlayerCharacter> OwningPlayerCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterMovementComponent> PlayerCharacterMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	FVector Velocity;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	bool bIsFalling;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	float LocomotionDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	EStateType StateType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimData|LocomotionData", meta = (AllowPrivateAccess = "true"))
	EWeaponType CurrentWeaponType;
};
