// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Other/ItemStruct.h"
#include "QuestItemSlotWidget.generated.h"

class UInventoryComponent;
class UQuestItemActionMenu;

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UQuestItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UQuestItemSlotWidget(const FObjectInitializer& ObjectInitializer);


#pragma region Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|SlotData")
	int32 QuestItemSlotIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|SlotData")
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Slot Widget|Variable|ActionMenu")
	TObjectPtr<UQuestItemActionMenu> QuestItemActionMenu;
#pragma endregion


#pragma region Function
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSlot();

	UFUNCTION(BlueprintPure)
	const FItemData& GetSlotData();
#pragma endregion
};
