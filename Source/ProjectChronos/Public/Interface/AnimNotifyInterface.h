// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AnimNotifyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimNotifyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTCHRONOS_API IAnimNotifyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.


#pragma region Dash
public:
	virtual void DashEnded() = 0;
	virtual void DashInvincibleStart() = 0;
	virtual void DashInvincibleEnd() = 0;
#pragma endregion


#pragma region Combo Attack
public:
	virtual void ResetComboAttack() = 0;
	virtual void ComboStart() = 0;

	virtual void ComboWindowStart() = 0;
	virtual void ComboWindowEnd() = 0;
#pragma endregion


#pragma region Heavy Attack
	virtual void HeavyAttackEnd() = 0;
#pragma endregion


#pragma region Attack Rotation
public:
	virtual void RotationStartWhenAttack() = 0;
	virtual void RotationEndWhenAttack() = 0;
#pragma endregion


#pragma region Just Guard
public:
	virtual void JustGuardStart() = 0;
	virtual void JustGuardEnd() = 0;
#pragma endregion


#pragma region Holster Weapon Equip
public:
	virtual void EquipWeapon1() = 0;
	virtual void EquipWeapon2() = 0;
	virtual void WeaponSwitchingEnd() = 0;
#pragma endregion
};
