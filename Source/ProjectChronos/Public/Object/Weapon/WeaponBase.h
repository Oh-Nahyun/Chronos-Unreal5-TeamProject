// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Other/Enums.h"
#include "WeaponBase.generated.h"

class UAnimMontage;

UCLASS()
class PROJECTCHRONOS_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:
	AWeaponBase();

protected:
	virtual void BeginPlay() override;


#pragma region Variable
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Variable")
	EWeaponType WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon|Variable")
	EWeaponEquipStateType WeaponEquipState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Montages")
	TArray<TSoftObjectPtr<UAnimMontage>> ComboMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Montages")
	TSoftObjectPtr<UAnimMontage> HeavyAttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Montages")
	TSoftObjectPtr<UAnimMontage> GuardMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Montages")
	TSoftObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Variable")
	TObjectPtr<ACharacter> OwnerPlayerCharacter;

	UFUNCTION(BlueprintImplementableEvent)
	void AttachOnPlayerCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void EquipOnPlayerCharacter();

	UFUNCTION(BlueprintImplementableEvent)
	void DetachOnPlayerCharacter();
#pragma endregion
};
