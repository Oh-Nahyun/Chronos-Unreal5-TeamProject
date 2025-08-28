// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/Slot/ConsumableSlotWidget.h"

#include "Component/InventoryComponent.h"

#include "Other/Debug.h"

UConsumableSlotWidget::UConsumableSlotWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	ConsumableSlotIndex = -1;
}

const FConsumableData& UConsumableSlotWidget::GetSlotData()
{
	return InventoryComponent.Get()->ConsumableArray[ConsumableSlotIndex];
}
