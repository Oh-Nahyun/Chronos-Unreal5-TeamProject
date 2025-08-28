// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Other/ItemStruct.h"
#include "MaterialSlotWidget.generated.h"

class UInventoryComponent;
class UMaterialActionMenu;

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UMaterialSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMaterialSlotWidget(const FObjectInitializer& ObjectInitializer);


#pragma region Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|SlotData")
	int32 MaterialSlotIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|SlotData")
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|ActionMenu")
	TObjectPtr<UMaterialActionMenu> MaterialActionMenu;
#pragma endregion


#pragma region Function
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSlot();

	UFUNCTION(BlueprintPure)
	const FItemData& GetSlotData();
#pragma endregion
};
