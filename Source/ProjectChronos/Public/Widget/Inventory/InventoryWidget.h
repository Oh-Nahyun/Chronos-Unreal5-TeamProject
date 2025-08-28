// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Other/ItemStruct.h"
#include "InventoryWidget.generated.h"

class UInventoryComponent;
class UWrapBox;
class UWeaponSlotWidget;
class UArmorSlotWidget;
class UConsumableSlotWidget;
class UMaterialSlotWidget;
class UQuestItemSlotWidget;
class UWeaponActionMenu;
class UArmorActionMenu;
class UConsumableActionMenu;
class UMaterialActionMenu;
class UQuestItemActionMenu;
class UDropWidget;
class UEquipedArmorSlot;
class UEquipedArmorActionMenu;
class UEquipedWeaponSlot;
class UEquipedWeaponActionMenu;

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);


#pragma region Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable")
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;
#pragma endregion


#pragma region Slot
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|Slot", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UWeaponSlotWidget> WeaponSlotWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|Slot", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UArmorSlotWidget> ArmorSlotWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|Slot", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UConsumableSlotWidget> ConsumableSlotWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|Slot", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMaterialSlotWidget> MaterialSlotWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|Slot", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UQuestItemSlotWidget> QuestItemSlotWidgetClass;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|SlotArray")
	TArray<TObjectPtr<UWeaponSlotWidget>> WeaponSlotWidgets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|SlotArray")
	TArray<TObjectPtr<UArmorSlotWidget>> ArmorSlotWidgets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|SlotArray")
	TArray<TObjectPtr<UConsumableSlotWidget>> ConsumableSlotWidgets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|SlotArray")
	TArray<TObjectPtr<UMaterialSlotWidget>> MaterialSlotWidgets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|SlotArray")
	TArray<TObjectPtr<UQuestItemSlotWidget>> QuestItemSlotWidgets;
#pragma endregion


#pragma region Equiped Armor Slot
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|EquipedSlot", meta = (BindWidget))
	TObjectPtr<UEquipedArmorSlot> EquipedHeadArmorSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|EquipedSlot", meta = (BindWidget))
	TObjectPtr<UEquipedArmorSlot> EquipedChestArmorSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|EquipedSlot", meta = (BindWidget))
	TObjectPtr<UEquipedArmorSlot> EquipedLegArmorSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|EquipedSlot", meta = (BindWidget))
	TObjectPtr<UEquipedArmorSlot> EquipedShoesArmorSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|EquipedSlot", meta = (BindWidget))
	TObjectPtr<UEquipedArmorSlot> EquipedAccessoriesArmorSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|EquipedSlot", meta = (BindWidget))
	TObjectPtr<UEquipedWeaponSlot> EquipedWeapon1Slot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|EquipedSlot", meta = (BindWidget))
	TObjectPtr<UEquipedWeaponSlot> EquipedWeapon2Slot;
#pragma endregion


#pragma region Action Menu
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UWeaponActionMenu> WeaponActionMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponActionMenu> WeaponActionMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UArmorActionMenu> ArmorActionMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArmorActionMenu> ArmorActionMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UConsumableActionMenu> ConsumableActionMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UConsumableActionMenu> ConsumableActionMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UMaterialActionMenu> MaterialActionMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialActionMenu> MaterialActionMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UQuestItemActionMenu> QuestItemActionMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UQuestItemActionMenu> QuestItemActionMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UEquipedArmorActionMenu> EquipedArmorActionMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipedArmorActionMenu> EquipedArmorActionMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UEquipedWeaponActionMenu> EquipedWeaponActionMenuClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|ActionMenu", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEquipedWeaponActionMenu> EquipedWeaponActionMenuWidget;
#pragma endregion


#pragma region Drop Menu
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Widget|Variable|DropMenu", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDropWidget> DropWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|DropMenu", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDropWidget> DropWidget;
#pragma endregion


#pragma region Inventory Tab
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|Tab", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UWrapBox> WeaponTab;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|Tab", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UWrapBox> ArmorTab;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|Tab", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UWrapBox> ConsumableTab;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|Tab", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UWrapBox> MaterialTab;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Widget|Variable|Tab", meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UWrapBox> QuestItemTab;
#pragma endregion


#pragma region Initialize Function
public:
	void InitializeAllTabs();

	void InitializeWeaponTab();
	void InitializeArmorTab();
	void InitializeConsumableTab();
	void InitializeMaterialTab();
	void InitializeQuestItemTab();
#pragma endregion


#pragma region Update Function
public:
	//// Weapon
	void UpdateWeaponTab();
	////

	//// Armor
	void UpdateArmorTab();
	////

	//// Consumable
	void UpdateConsumableTab();
	////

	//// Material
	void UpdateMaterialTab();
	////

	//// Quest item
	void UpdateQuestItemTab();
	////

	//// Equiped or unequip armor and weapon slot
	void UpdateEquipedArmorSlot(uint8 InArmorType, int32 SlotIndex);
	void UnEquipArmorSlot(uint8 InArmorType);

	void UpdateEquipedWeaponSlot(uint8 InWeaponType, int32 SlotIndex);
	void UnEquipWeaponSlot(uint8 InWeaponType);
	////
#pragma endregion
};
