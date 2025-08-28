// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/ActionMenu/MaterialActionMenu.h"

UMaterialActionMenu::UMaterialActionMenu(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{
	MaterialSlotIndex = -1;
}

void UMaterialActionMenu::SetData(const int32& InMaterialSlotIndex)
{
	MaterialSlotIndex = InMaterialSlotIndex;
}
