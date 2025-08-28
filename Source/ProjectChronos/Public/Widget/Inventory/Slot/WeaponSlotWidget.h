// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Other/ItemStruct.h"
#include "WeaponSlotWidget.generated.h"

class UInventoryComponent;
class UWeaponActionMenu;

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UWeaponSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UWeaponSlotWidget(const FObjectInitializer& ObjectInitializer);


#pragma region Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|SlotData")
	int32 WeaponSlotIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|SlotData")
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|ActionMenu")
	TObjectPtr<UWeaponActionMenu> WeaponActionMenu;
#pragma endregion


#pragma region Function
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSlot();

	UFUNCTION(BlueprintPure)
	const FWeaponData& GetSlotData();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EquipOnSlot();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UnEquipOnSlot();
#pragma endregion
};
