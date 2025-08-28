#pragma once

#include "CoreMinimal.h"
#include "Other/Enums.h"
#include "ItemStruct.generated.h"

class UTexture2D;
class USkeletalMesh;
class AWeaponBase;

USTRUCT(Blueprintable, BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FName ItemID = FName();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FText ItemName = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FText ItemDescription = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TSoftObjectPtr<UTexture2D> ItemIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	int32 StackSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	int32 ItemQuantity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EItemRankType ItemRank = EItemRankType::None;
};

USTRUCT(Blueprintable, BlueprintType)
struct FWeaponData : public FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EWeaponSlotType WeaponSlotType = EWeaponSlotType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EWeaponType WeaponType = EWeaponType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TSoftClassPtr<AWeaponBase> WeaponClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	float WeaponPower = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	bool IsEquiped = false;
};

USTRUCT(Blueprintable, BlueprintType)
struct FArmorData : public FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EArmorType ArmorType = EArmorType::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TSoftObjectPtr<USkeletalMesh> ArmorMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	float ArmorDefense = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	bool IsEquiped = false;
};

USTRUCT(Blueprintable, BlueprintType)
struct FConsumableData : public FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	float HealAmount = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Item Data")
	int8 QuickSlotIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	bool IsEquiped = false;
};
