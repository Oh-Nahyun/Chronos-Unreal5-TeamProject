// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/ActionMenu/ArmorActionMenu.h"

UArmorActionMenu::UArmorActionMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	ArmorSlotIndex = -1;
}

void UArmorActionMenu::SetData(const int32& InArmorSlotIndex)
{
	ArmorSlotIndex = InArmorSlotIndex;
}
