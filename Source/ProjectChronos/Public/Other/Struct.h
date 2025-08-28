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
	float JumpStaminaUse;				// 점프 스태미너 소모량

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	float DashStaminaUse;				// 회피 스태미너 소모량

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	float LightAttackStaminaUse;		// 약공격 스태미너 소모량

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	float HeavyAttackStaminaUse;		// 강공격 스태미너 소모량

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	float GuardSuccessStaminaUse;		// 막기 성공 스태미너 소모량

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Status")
	float StaminaRegenAmount;			// 스태미너 리젠량
};

USTRUCT(Blueprintable, BlueprintType)
struct FWeaponStatus
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float Attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float CriticalChance;				// 치명타 확률

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float CriticalDamageCoefficient;	// 치명타 데미지 배율

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
