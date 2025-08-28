// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/ActionMenu/WeaponActionMenu.h"

UWeaponActionMenu::UWeaponActionMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	WeaponSlotIndex = -1;
}

void UWeaponActionMenu::SetData(const int32& InWeaponSlotIndex)
{
	WeaponSlotIndex = InWeaponSlotIndex;
}
