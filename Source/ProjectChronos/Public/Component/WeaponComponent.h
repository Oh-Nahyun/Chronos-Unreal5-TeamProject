// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Other/Enums.h"
#include "WeaponComponent.generated.h"

class AWeaponBase;
class ACPlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCHRONOS_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;


#pragma region Owner
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACPlayerCharacter> OwningPlayerCharacter;

public:
	void InitializeOwner();
#pragma endregion
	

#pragma region Variable
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Weapon|Variable", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponBase> MeleeWeaponClass;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Weapon|Variable", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeaponBase> MeleeWeapon;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Weapon|Variable", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponBase> RangeWeaponClass;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Weapon|Variable", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeaponBase> RangeWeapon;

private:
	uint8 CurrentComboCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Weapon|Attack", meta = (AllowPrivateAccess = "true"))
	uint8 MaxComboCount;

	bool bIsAttacking;

public:
	bool GetIsAttacking() const { return bIsAttacking; }

public:
	bool bCanNextCombo;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component|Weapon|State")
	uint8 CurrentWeaponState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component|Weapon|State")
	EWeaponModeType CurrentWeaponMode;
#pragma endregion


#pragma region Weapon Anims
private:
	//// Melee Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Weapon|Anim", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> MeleeWeaponComboAnims;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Weapon|Anim", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> MeleeWeaponHeavyAttackAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Weapon|Anim", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> MeleeWeaponGuardAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Weapon|Anim", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> MeleeWeaponEquipAnim;
	////

	//// Range Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Weapon|Anim", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UAnimMontage>> RangeWeaponComboAnims;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Weapon|Anim", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> RangeWeaponHeavyAttackAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Weapon|Anim", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> RangeWeaponEquipAnim;
	////
#pragma endregion


#pragma region Function
public:
	//// Spawn and equip or unequip weapon
	void SpawnMeleeWeapon(TSoftClassPtr<AWeaponBase> InWeaponClass);
	void SpawnRangeWeapon(TSoftClassPtr<AWeaponBase> InWeaponClass);

	void UnEquipWeapon(uint8 InWeaponType);
	////

	//// Attack
	void DoLightAttack();
	void DoHeavyAttack();

private:
	void SetComboCount();

public:
	void ResetCombo();
	////

	//// Guard
	void DoGuard();
	////

	//// Switching
	const EWeaponType WeaponSwitching();
	void EquipMeleeWeapon();
	void EquipRangeWeapon();
	////
#pragma endregion
};
