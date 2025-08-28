// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/Slot/WeaponSlotWidget.h"

#include "Component/InventoryComponent.h"

UWeaponSlotWidget::UWeaponSlotWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	WeaponSlotIndex = -1;
}

const FWeaponData& UWeaponSlotWidget::GetSlotData()
{
	return InventoryComponent.Get()->WeaponArray[WeaponSlotIndex];
}
