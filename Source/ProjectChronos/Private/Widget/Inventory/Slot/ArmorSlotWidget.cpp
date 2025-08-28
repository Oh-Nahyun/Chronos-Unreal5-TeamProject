// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/Slot/ArmorSlotWidget.h"

#include "Component/InventoryComponent.h"

UArmorSlotWidget::UArmorSlotWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	ArmorSlotIndex = -1;
}

const FArmorData& UArmorSlotWidget::GetSlotData()
{
	return InventoryComponent.Get()->ArmorArray[ArmorSlotIndex];
}
