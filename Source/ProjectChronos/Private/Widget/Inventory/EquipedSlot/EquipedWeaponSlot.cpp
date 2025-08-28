// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/EquipedSlot/EquipedWeaponSlot.h"

#include "Component/InventoryComponent.h"

UEquipedWeaponSlot::UEquipedWeaponSlot(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	WeaponSlotIndex = -1;
	WeaponSlotType = 0;
}

const FWeaponData& UEquipedWeaponSlot::GetSlotData()
{
	return InventoryComponent.Get()->WeaponArray[WeaponSlotIndex];
}
