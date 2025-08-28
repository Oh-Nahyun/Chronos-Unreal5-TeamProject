// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Other/ItemStruct.h"
#include "EquipedWeaponSlot.generated.h"

class UInventoryComponent;
class UEquipedWeaponActionMenu;

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UEquipedWeaponSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UEquipedWeaponSlot(const FObjectInitializer& ObjectInitializer);


#pragma region Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equiped Slot Widget|Variable|SlotData")
	int32 WeaponSlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equiped Slot Widget|Variable|SlotData")
	uint8 WeaponSlotType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equiped Slot Widget|Variable|SlotData")
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equiped Slot Widget|Variable|ActionMenu")
	TObjectPtr<UEquipedWeaponActionMenu> EquipedWeaponActionMenu;
#pragma endregion


#pragma region Function
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSlot();

	UFUNCTION(BlueprintImplementableEvent)
	void UnEquipUpdateSlot();

	UFUNCTION(BlueprintPure)
	const FWeaponData& GetSlotData();
#pragma endregion
};
