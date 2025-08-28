// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/Slot/QuestItemSlotWidget.h"

#include "Component/InventoryComponent.h"

UQuestItemSlotWidget::UQuestItemSlotWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	QuestItemSlotIndex = -1;
}

const FItemData& UQuestItemSlotWidget::GetSlotData()
{
	return InventoryComponent.Get()->QuestItemArray[QuestItemSlotIndex];
}
