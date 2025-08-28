// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/ActionMenu/ConsumableActionMenu.h"

UConsumableActionMenu::UConsumableActionMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	ConsumableSlotIndex = -1;
}

void UConsumableActionMenu::SetData(const int32& InConsumableSlotIndex)
{
	ConsumableSlotIndex = InConsumableSlotIndex;
}
