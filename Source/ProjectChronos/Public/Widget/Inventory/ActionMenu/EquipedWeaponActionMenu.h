// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipedWeaponActionMenu.generated.h"

class UInventoryComponent;

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UEquipedWeaponActionMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UEquipedWeaponActionMenu(const FObjectInitializer& ObjectInitializer);


#pragma region Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equiped Action Menu Widget|Variable")
	int32 WeaponSlotIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equiped Action Menu Widget|Variable")
	uint8 WeaponSlotType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equiped Action Menu Widget|Variable")
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;
#pragma endregion


#pragma region Function
public:
	UFUNCTION(BlueprintCallable)
	void SetData(const int32& InWeaponSlotIndex, uint8 InWeaponSlotType);
#pragma endregion
};
