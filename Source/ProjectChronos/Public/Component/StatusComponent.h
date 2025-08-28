// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Other/Enums.h"
#include "StatusComponent.generated.h"

class UCPlayerCharacterStatusData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCHRONOS_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatusComponent();

protected:
	virtual void BeginPlay() override;

public:	
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


#pragma region Data
private:
	UPROPERTY(EditDefaultsOnly, Category = "Status|Data")
	TObjectPtr<UCPlayerCharacterStatusData> StatusDataAsset;
#pragma endregion


#pragma region Max Status
private:
	//// Base status
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status|Base", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status|Base", meta = (AllowPrivateAccess = "true"))
	float MaxStamina;
	////

	//// Stamina use status
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status|Stamina Use", meta = (AllowPrivateAccess = "true"))
	float JumpStaminaUse;				// ���� ���¹̳� �Ҹ�

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status|Stamina Use", meta = (AllowPrivateAccess = "true"))
	float DashStaminaUse;				// ȸ�� ���¹̳� �Ҹ�

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status|Stamina Use", meta = (AllowPrivateAccess = "true"))
	float LightAttackStaminaUse;		// ����� ���¹̳� �Ҹ�

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status|Stamina Use", meta = (AllowPrivateAccess = "true"))
	float HeavyAttackStaminaUse;		// ������ ���¹̳� �Ҹ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Status|Stamina Use", meta = (AllowPrivateAccess = "true"))
	float GuardSuccessStaminaUse;		// ���� ���� ���¹̳� �Ҹ�
	////

	//// Stamina regen status
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Status|Stamina Regen", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenAmount;			// ���¹̳� ������

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Status|Stamina Regen", meta = (AllowPrivateAccess = "true"))
	float StaminaRegenPeriod;			// ���¹̳� ���� �ֱ�
#pragma endregion


#pragma region Current Status
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status|Base", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status|Base", meta = (AllowPrivateAccess = "true"))
	float CurrentStamina;

	//// Combat status
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status|Combat", meta = (AllowPrivateAccess = "true"))
	float Attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status|Combat", meta = (AllowPrivateAccess = "true"))
	float Defense;
	////

	//// Critical status
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status|Combat", meta = (AllowPrivateAccess = "true"))
	float CriticalChance;				// ġ��Ÿ Ȯ��

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status|Combat", meta = (AllowPrivateAccess = "true"))
	float CriticalDamageCoefficient;	// ġ��Ÿ ������ ����
	////
#pragma endregion


#pragma region Function
public:
	//// Initialize
	void InitStatusData();
	////

	//// Stamina
	void UseStamina(EActionType InActionType);
	bool CanDoAction(EActionType InActionType);
	////

	//// Blocking
	void StartBlocking();
	void EndBlocking();
	void GuardSuccess();
	////
#pragma endregion


#pragma region Regen
private:
	FTimerHandle StaminaRegenTimerHandle;
	FTimerHandle RegenStopTimerHandle;

	void RegenStamina();
	void StopRegen();
	void StartRegen();
#pragma endregion


#pragma region Damage
public:
	float TakeDamage(float InDamage);
#pragma endregion
};
