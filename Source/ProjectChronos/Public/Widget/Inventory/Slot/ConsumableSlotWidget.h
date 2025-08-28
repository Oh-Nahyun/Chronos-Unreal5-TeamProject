// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Other/ItemStruct.h"
#include "ConsumableSlotWidget.generated.h"

class UInventoryComponent;
class UConsumableActionMenu;

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UConsumableSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UConsumableSlotWidget(const FObjectInitializer& ObjectInitializer);


#pragma region Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|SlotData")
	int32 ConsumableSlotIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|SlotData")
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|ActionMenu")
	TObjectPtr<UConsumableActionMenu> ConsumableActionMenu;
#pragma endregion


#pragma region Function
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateSlot();

	UFUNCTION(BlueprintPure)
	const FConsumableData& GetSlotData();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EquipOnQuickSlot();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UnEquipOnQuickSlot();
#pragma endregion
};
