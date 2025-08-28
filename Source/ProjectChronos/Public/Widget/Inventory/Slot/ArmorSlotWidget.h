// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Other/ItemStruct.h"
#include "ArmorSlotWidget.generated.h"

class UInventoryComponent;
class UArmorActionMenu;

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UArmorSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UArmorSlotWidget(const FObjectInitializer& ObjectInitializer);


#pragma region Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|SlotData")
	int32 ArmorSlotIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|SlotData")
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|ActionMenu")
	TObjectPtr<UArmorActionMenu> ArmorActionMenu;
#pragma endregion


#pragma region Function
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSlot();

	UFUNCTION(BlueprintPure)
	const FArmorData& GetSlotData();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EquipOnSlot();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UnEquipOnSlot();
#pragma endregion
};
