#pragma once

#include "CoreMinimal.h"
#include "Struct.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FPlayerStatus
{
	GENERATED_BODY()

	// Base Status
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Base")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Base")
	float MaxStamina;

	// Stamina Status
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	float JumpStaminaUse;				// ���� ���¹̳� �Ҹ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	float DashStaminaUse;				// ȸ�� ���¹̳� �Ҹ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	float LightAttackStaminaUse;		// ����� ���¹̳� �Ҹ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	float HeavyAttackStaminaUse;		// ������ ���¹̳� �Ҹ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	float GuardSuccessStaminaUse;		// ���� ���� ���¹̳� �Ҹ�

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Status")
	float StaminaRegenAmount;			// ���¹̳� ������
};

USTRUCT(Blueprintable, BlueprintType)
struct FWeaponStatus
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float Attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float CriticalChance;				// ġ��Ÿ Ȯ��

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float CriticalDamageCoefficient;	// ġ��Ÿ ������ ����

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float AttackSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float ArmorPenetration;
};

USTRUCT(Blueprintable, BlueprintType)
struct FConversationData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Conversation")
	TSoftObjectPtr<UTexture2D> NPCImage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Conversation")
	FText NPCName;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Conversation")
	FText NPCLine;
};
