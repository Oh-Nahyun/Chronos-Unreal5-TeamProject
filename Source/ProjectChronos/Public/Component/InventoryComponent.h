// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Other/ItemStruct.h"
#include "InventoryComponent.generated.h"

class ACPlayerCharacter;
class ACPlayerController;
class UInventoryWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCHRONOS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;


#pragma region Owner
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Owner", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACPlayerCharacter> OwningPlayerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Owner", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACPlayerController> OwningPlayerController;

public:
	void InitializeOwner(ACPlayerCharacter* InOwnerPlayerCharacter);
	void InitializeOwnerController(ACPlayerController* InOwningPlayerController);
#pragma endregion

	
#pragma region Widget
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Widget")
	TObjectPtr<UInventoryWidget> InventoryWidget;

public:
	void CreateInventoryWidget();
	void OpenInventoryWidget();
#pragma endregion


#pragma region Variable
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Inventory|Array")
	TArray<FWeaponData> WeaponArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Inventory|Array")
	TArray<FArmorData> ArmorArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Inventory|Array")
	TArray<FConsumableData> ConsumableArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Inventory|Array")
	TArray<FItemData> MaterialArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Inventory|Array")
	TArray<FItemData> QuestItemArray;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Component|Inventory")
	uint8 InventorySize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component|Inventory|Array")
	TArray<int32> QuickSlotArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component|Inventory|Array")
	TArray<int32> ArmorEquipedSlotArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component|Inventory|Array")
	TArray<int32> WeaponEquipedSlotArray;
#pragma endregion


#pragma region Function
public:
	void InitializeInventorySlot();

	//// Item add
	bool AddWeapon(const FWeaponData& InWeaponData);
	bool AddArmor(const FArmorData& InArmorData);
	bool AddConsumable(const FConsumableData& InConsumableData);
	bool AddMaterial(const FItemData& InItemData);
	bool AddQuestItem(const FItemData& InQuestItemData);
	////

	//// Update inventory slot
	void UpdateWeaponTab();
	void UpdateArmorTab();
	void UpdateConsumableTab();
	void UpdateMaterialTab();
	void UpdateQuestItemTab();
	////

	//// Use or drop item in slot
	UFUNCTION(BlueprintCallable)
	void UseConsumable(int32 InSlotIndex);

	UFUNCTION(BlueprintCallable)
	void DropItem(uint8 InItemType, int32 InSlotIndex);
	////

	//// Equip item in slot
	UFUNCTION(BlueprintCallable)
	void EquipConsumableInQuickSlot(uint8 InQuickSlotIndex, int32 InSlotIndex);

	UFUNCTION(BlueprintCallable)
	void EquipArmor(int32 InSlotIndex);

	UFUNCTION(BlueprintCallable)
	void UnEquipArmor(uint8 InArmorType, int32 InSlotIndex);

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(int32 InSlotIndex);

	UFUNCTION(BlueprintCallable)
	void UnEquipWeapon(uint8 InWeaponType, int32 InSlotIndex);
	////

	//// Quick slot
	void UseQuickSlot(uint8 InQuickSlotIndex);
	////
#pragma endregion
};
