// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/ActionMenu/EquipedArmorActionMenu.h"

UEquipedArmorActionMenu::UEquipedArmorActionMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	ArmorSlotIndex = -1;
	ArmorSlotType = 0;
}

void UEquipedArmorActionMenu::SetData(const int32& InArmorSlotIndex, uint8 InArmorSlotType)
{
	ArmorSlotIndex = InArmorSlotIndex;
	ArmorSlotType = InArmorSlotType;
}
