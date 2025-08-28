// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/DropUI/DropWidget.h"

UDropWidget::UDropWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SlotIndex = 0;
	ItemType = EItemType::None;
}

void UDropWidget::SetData(const int32& InSlotIndex, EItemType InItemType)
{
	SlotIndex = InSlotIndex;
	ItemType = InItemType;
}
