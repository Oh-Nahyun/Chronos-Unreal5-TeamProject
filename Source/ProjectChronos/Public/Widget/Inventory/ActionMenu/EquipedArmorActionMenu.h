// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipedArmorActionMenu.generated.h"

class UInventoryComponent;

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UEquipedArmorActionMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UEquipedArmorActionMenu(const FObjectInitializer& ObjectInitializer);


#pragma region Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equiped Action Menu Widget|Variable")
	int32 ArmorSlotIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equiped Action Menu Widget|Variable")
	uint8 ArmorSlotType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equiped Action Menu Widget|Variable")
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;
#pragma endregion


#pragma region Function
public:
	UFUNCTION(BlueprintCallable)
	void SetData(const int32& InArmorSlotIndex, uint8 InArmorSlotType);
#pragma endregion
};
