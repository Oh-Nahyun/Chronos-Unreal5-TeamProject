#pragma once

UENUM(BlueprintType)
enum class EActorType : uint8
{
	PlayerCharacter = 0,
	ENPC,
	InteractableObject
};

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle = 0,
	Jumping,
	Dashing,
	LightAttacking,
	HeavyAttacking,
	HeavyAttackCharging,
	Guarding,
	Switching,
	ZoomIn
};

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Jump,
	Dash,
	LightAttack,
	HeavyAttack,
	Block
};

UENUM(BlueprintType)
enum class EInteractableActorType : uint8
{
	DropItem = 0,
	NPC,
	Shop,
	Landscape,
	SavePoint
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None = 0,
	Weapon,
	Armor,
	Consumable,
	Material,
	QuestItem
};

UENUM(BlueprintType)
enum class EItemRankType : uint8
{
	None = 0,
	Common,
	Epic,
	Legendary
};

UENUM(BlueprintType)
enum class EWeaponSlotType : uint8
{
	None = 0,
	Switching1,
	Switching2
};

UENUM(BlueprintType)
enum class EWeaponModeType : uint8
{
	None = 0,
	MeleeMode,
	RangeMode
};

UENUM(BlueprintType)
enum class EWeaponEquipStateType : uint8
{
	None = 0,
	Attached,
	Equipped
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None = 0,
	DualSword,
	LongSword,
	GreatSword,
	Rifle
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	None = 0,
	Head,
	Chest,
	Leg,
	Shoes,
	Accessories
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	None = 0,
	Normal,
	Hard,
	Area,
	Range
};
