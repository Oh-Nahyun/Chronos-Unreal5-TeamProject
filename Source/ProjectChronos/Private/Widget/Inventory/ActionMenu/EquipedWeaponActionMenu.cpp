// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/ActionMenu/EquipedWeaponActionMenu.h"

UEquipedWeaponActionMenu::UEquipedWeaponActionMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	WeaponSlotIndex = -1;
	WeaponSlotType = 0;
}

void UEquipedWeaponActionMenu::SetData(const int32& InWeaponSlotIndex, uint8 InWeaponSlotType)
{
	WeaponSlotIndex = InWeaponSlotIndex;
	WeaponSlotType = InWeaponSlotType;
}
