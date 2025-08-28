// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/Slot/MaterialSlotWidget.h"

#include "Component/InventoryComponent.h"

UMaterialSlotWidget::UMaterialSlotWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	MaterialSlotIndex = -1;
}

const FItemData& UMaterialSlotWidget::GetSlotData()
{
	return InventoryComponent.Get()->MaterialArray[MaterialSlotIndex];
}
