// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/ActionMenu/QuestItemActionMenu.h"

UQuestItemActionMenu::UQuestItemActionMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	QuestItemSlotIndex = -1;
}

void UQuestItemActionMenu::SetData(const int32& InQuestItemSlotIndex)
{
	QuestItemSlotIndex = InQuestItemSlotIndex;
}
