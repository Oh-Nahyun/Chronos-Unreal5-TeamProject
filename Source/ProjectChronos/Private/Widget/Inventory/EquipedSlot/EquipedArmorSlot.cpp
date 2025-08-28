// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/EquipedSlot/EquipedArmorSlot.h"

#include "Component/InventoryComponent.h"

UEquipedArmorSlot::UEquipedArmorSlot(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	ArmorSlotIndex = -1;
	ArmorSlotType = 0;
}

const FArmorData& UEquipedArmorSlot::GetSlotData()
{
	return InventoryComponent.Get()->ArmorArray[ArmorSlotIndex];
}
