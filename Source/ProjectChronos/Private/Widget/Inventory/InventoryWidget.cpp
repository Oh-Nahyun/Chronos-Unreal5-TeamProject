// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Inventory/InventoryWidget.h"

#include "Components/WrapBox.h"

#include "Widget/Inventory/Slot/WeaponSlotWidget.h"
#include "Widget/Inventory/Slot/ArmorSlotWidget.h"
#include "Widget/Inventory/Slot/ConsumableSlotWidget.h"
#include "Widget/Inventory/Slot/MaterialSlotWidget.h"
#include "Widget/Inventory/Slot/QuestItemSlotWidget.h"
#include "Widget/Inventory/EquipedSlot/EquipedArmorSlot.h"
#include "Widget/Inventory/EquipedSlot/EquipedWeaponSlot.h"
#include "Widget/Inventory/ActionMenu/WeaponActionMenu.h"
#include "Widget/Inventory/ActionMenu/ArmorActionMenu.h"
#include "Widget/Inventory/ActionMenu/ConsumableActionMenu.h"
#include "Widget/Inventory/ActionMenu/MaterialActionMenu.h"
#include "Widget/Inventory/ActionMenu/QuestItemActionMenu.h"
#include "Widget/Inventory/ActionMenu/EquipedArmorActionMenu.h"
#include "Widget/Inventory/ActionMenu/EquipedWeaponActionMenu.h"
#include "Component/InventoryComponent.h"
#include "Widget/Inventory/DropUI/DropWidget.h"

#include "Other/Debug.h"

UInventoryWidget::UInventoryWidget(const FObjectInitializer& ObjectInitializer)
	: UUserWidget(ObjectInitializer)
{

}

void UInventoryWidget::InitializeAllTabs()
{
	if (!InventoryComponent.Get())
	{
		return;
	}

	WeaponActionMenuWidget = CreateWidget<UWeaponActionMenu>(GetWorld()->GetFirstPlayerController(), WeaponActionMenuClass);
	WeaponActionMenuWidget->InventoryComponent = InventoryComponent.Get();

	ArmorActionMenuWidget = CreateWidget<UArmorActionMenu>(GetWorld()->GetFirstPlayerController(), ArmorActionMenuClass);
	ArmorActionMenuWidget->InventoryComponent = InventoryComponent.Get();

	ConsumableActionMenuWidget = CreateWidget<UConsumableActionMenu>(GetWorld()->GetFirstPlayerController(), ConsumableActionMenuClass);
	ConsumableActionMenuWidget->InventoryComponent = InventoryComponent.Get();

	MaterialActionMenuWidget = CreateWidget<UMaterialActionMenu>(GetWorld()->GetFirstPlayerController(), MaterialActionMenuClass);
	MaterialActionMenuWidget->InventoryComponent = InventoryComponent.Get();

	QuestItemActionMenuWidget = CreateWidget<UQuestItemActionMenu>(GetWorld()->GetFirstPlayerController(), QuestItemActionMenuClass);
	QuestItemActionMenuWidget->InventoryComponent = InventoryComponent.Get();

	DropWidget = CreateWidget<UDropWidget>(GetWorld()->GetFirstPlayerController(), DropWidgetClass);
	DropWidget->InventoryComponent = InventoryComponent.Get();

	EquipedArmorActionMenuWidget = CreateWidget<UEquipedArmorActionMenu>(GetWorld()->GetFirstPlayerController(), EquipedArmorActionMenuClass);
	EquipedArmorActionMenuWidget->InventoryComponent = InventoryComponent.Get();

	EquipedWeaponActionMenuWidget = CreateWidget<UEquipedWeaponActionMenu>(GetWorld()->GetFirstPlayerController(), EquipedWeaponActionMenuClass);
	EquipedWeaponActionMenuWidget->InventoryComponent = InventoryComponent.Get();

	EquipedHeadArmorSlot->InventoryComponent = InventoryComponent.Get();
	EquipedHeadArmorSlot->EquipedArmorActionMenu = EquipedArmorActionMenuWidget;
	EquipedChestArmorSlot->InventoryComponent = InventoryComponent.Get();
	EquipedChestArmorSlot->EquipedArmorActionMenu = EquipedArmorActionMenuWidget;
	EquipedLegArmorSlot->InventoryComponent = InventoryComponent.Get();
	EquipedLegArmorSlot->EquipedArmorActionMenu = EquipedArmorActionMenuWidget;
	EquipedShoesArmorSlot->InventoryComponent = InventoryComponent.Get();
	EquipedShoesArmorSlot->EquipedArmorActionMenu = EquipedArmorActionMenuWidget;
	EquipedAccessoriesArmorSlot->InventoryComponent = InventoryComponent.Get();
	EquipedAccessoriesArmorSlot->EquipedArmorActionMenu = EquipedArmorActionMenuWidget;

	EquipedWeapon1Slot->InventoryComponent = InventoryComponent.Get();
	EquipedWeapon1Slot->EquipedWeaponActionMenu = EquipedWeaponActionMenuWidget;
	EquipedWeapon2Slot->InventoryComponent = InventoryComponent.Get();
	EquipedWeapon2Slot->EquipedWeaponActionMenu = EquipedWeaponActionMenuWidget;

	InitializeWeaponTab();
	InitializeArmorTab();
	InitializeConsumableTab();
	InitializeMaterialTab();
	InitializeQuestItemTab();
}

void UInventoryWidget::InitializeWeaponTab()
{
	if (!InventoryComponent.Get())
	{
		return;
	}

	for (int i = 0; i < InventoryComponent->InventorySize; i++)
	{
		UWeaponSlotWidget* WeaponSlot = CreateWidget<UWeaponSlotWidget>(GetWorld()->GetFirstPlayerController(), WeaponSlotWidgetClass);
		WeaponSlotWidgets[i] = WeaponSlot;
		WeaponSlot->WeaponSlotIndex = i;
		WeaponSlot->InventoryComponent = InventoryComponent.Get();
		WeaponSlot->WeaponActionMenu = WeaponActionMenuWidget;
		WeaponSlot->UpdateSlot();

		WeaponTab->AddChildToWrapBox(WeaponSlot);
	}
}

void UInventoryWidget::InitializeArmorTab()
{
	if (!InventoryComponent.Get())
	{
		return;
	}

	for (int i = 0; i < InventoryComponent->InventorySize; i++)
	{
		UArmorSlotWidget* ArmorSlot = CreateWidget<UArmorSlotWidget>(GetWorld()->GetFirstPlayerController(), ArmorSlotWidgetClass);
		ArmorSlotWidgets[i] = ArmorSlot;
		ArmorSlot->ArmorSlotIndex = i;
		ArmorSlot->InventoryComponent = InventoryComponent.Get();
		ArmorSlot->ArmorActionMenu = ArmorActionMenuWidget;
		ArmorSlot->UpdateSlot();

		ArmorTab->AddChildToWrapBox(ArmorSlot);
	}
}

void UInventoryWidget::InitializeConsumableTab()
{
	if (!InventoryComponent.Get())
	{
		return;
	}

	for (int i = 0; i < InventoryComponent->InventorySize; i++)
	{
		UConsumableSlotWidget* ConsumableSlot = CreateWidget<UConsumableSlotWidget>(GetWorld()->GetFirstPlayerController(), ConsumableSlotWidgetClass);
		ConsumableSlotWidgets[i] = ConsumableSlot;
		ConsumableSlot->ConsumableSlotIndex = i;
		ConsumableSlot->InventoryComponent = InventoryComponent.Get();
		ConsumableSlot->ConsumableActionMenu = ConsumableActionMenuWidget;
		ConsumableSlot->UpdateSlot();

		ConsumableTab->AddChildToWrapBox(ConsumableSlot);
	}
}

void UInventoryWidget::InitializeMaterialTab()
{
	if (!InventoryComponent.Get())
	{
		return;
	}

	for (int i = 0; i < InventoryComponent->InventorySize; i++)
	{
		UMaterialSlotWidget* MaterialSlot = CreateWidget<UMaterialSlotWidget>(GetWorld()->GetFirstPlayerController(), MaterialSlotWidgetClass);
		MaterialSlotWidgets[i] = MaterialSlot;
		MaterialSlot->MaterialSlotIndex = i;
		MaterialSlot->InventoryComponent = InventoryComponent.Get();
		MaterialSlot->MaterialActionMenu = MaterialActionMenuWidget;
		MaterialSlot->UpdateSlot();

		MaterialTab->AddChildToWrapBox(MaterialSlot);
	}
}

void UInventoryWidget::InitializeQuestItemTab()
{
	if (!InventoryComponent.Get())
	{
		return;
	}

	for (int i = 0; i < InventoryComponent->InventorySize; i++)
	{
		UQuestItemSlotWidget* QuestItemSlot = CreateWidget<UQuestItemSlotWidget>(GetWorld()->GetFirstPlayerController(), QuestItemSlotWidgetClass);
		QuestItemSlotWidgets[i] = QuestItemSlot;
		QuestItemSlot->QuestItemSlotIndex = i;
		QuestItemSlot->InventoryComponent = InventoryComponent.Get();
		QuestItemSlot->QuestItemActionMenu = QuestItemActionMenuWidget;
		QuestItemSlot->UpdateSlot();

		QuestItemTab->AddChildToWrapBox(QuestItemSlot);
	}
}

void UInventoryWidget::UpdateWeaponTab()
{
	if (!InventoryComponent.Get())
	{
		return;
	}

	for (UWeaponSlotWidget* WeaponSlot : WeaponSlotWidgets)
	{
		WeaponSlot->UpdateSlot();
	}
}

void UInventoryWidget::UpdateArmorTab()
{
	if (!InventoryComponent.Get())
	{
		return;
	}

	for (UArmorSlotWidget* ArmorSlot : ArmorSlotWidgets)
	{
		ArmorSlot->UpdateSlot();
	}
}

void UInventoryWidget::UpdateConsumableTab()
{
	if (!InventoryComponent.Get())
	{
		return;
	}

	for (UConsumableSlotWidget* ConsumableSlot : ConsumableSlotWidgets)
	{
		ConsumableSlot->UpdateSlot();
	}
}

void UInventoryWidget::UpdateMaterialTab()
{
	if (!InventoryComponent.Get())
	{
		return;
	}

	for (UMaterialSlotWidget* MaterialSlot : MaterialSlotWidgets)
	{
		MaterialSlot->UpdateSlot();
	}
}

void UInventoryWidget::UpdateQuestItemTab()
{
	if (!InventoryComponent.Get())
	{
		return;
	}

	for (UQuestItemSlotWidget* QuestItemSlot : QuestItemSlotWidgets)
	{
		QuestItemSlot->UpdateSlot();
	}
}

void UInventoryWidget::UpdateEquipedArmorSlot(uint8 InArmorType, int32 SlotIndex)
{
	if (InArmorType == 0)
	{
		EquipedHeadArmorSlot->ArmorSlotIndex = SlotIndex;
		EquipedHeadArmorSlot->UpdateSlot();
	}
	else if (InArmorType == 1)
	{
		EquipedChestArmorSlot->ArmorSlotIndex = SlotIndex;
		EquipedChestArmorSlot->UpdateSlot();
	}
	else if (InArmorType == 2)
	{
		EquipedLegArmorSlot->ArmorSlotIndex = SlotIndex;
		EquipedLegArmorSlot->UpdateSlot();
	}
	else if (InArmorType == 3)
	{
		EquipedShoesArmorSlot->ArmorSlotIndex = SlotIndex;
		EquipedShoesArmorSlot->UpdateSlot();
	}
	else if (InArmorType == 4)
	{
		EquipedAccessoriesArmorSlot->ArmorSlotIndex = SlotIndex;
		EquipedAccessoriesArmorSlot->UpdateSlot();
	}
	else
	{
		return;
	}
}

void UInventoryWidget::UnEquipArmorSlot(uint8 InArmorType)
{
	if (InArmorType == 0)
	{
		EquipedHeadArmorSlot->ArmorSlotIndex = -1;
		EquipedHeadArmorSlot->UnEquipUpdateSlot();
	}
	else if (InArmorType == 1)
	{
		EquipedChestArmorSlot->ArmorSlotIndex = -1;
		EquipedChestArmorSlot->UnEquipUpdateSlot();
	}
	else if (InArmorType == 2)
	{
		EquipedLegArmorSlot->ArmorSlotIndex = -1;
		EquipedLegArmorSlot->UnEquipUpdateSlot();
	}
	else if (InArmorType == 3)
	{
		EquipedShoesArmorSlot->ArmorSlotIndex = -1;
		EquipedShoesArmorSlot->UnEquipUpdateSlot();
	}
	else if (InArmorType == 4)
	{
		EquipedAccessoriesArmorSlot->ArmorSlotIndex = -1;
		EquipedAccessoriesArmorSlot->UnEquipUpdateSlot();
	}
	else
	{
		return;
	}
}

void UInventoryWidget::UpdateEquipedWeaponSlot(uint8 InWeaponType, int32 SlotIndex)
{
	if (InWeaponType == 0)
	{
		EquipedWeapon1Slot->WeaponSlotIndex = SlotIndex;
		EquipedWeapon1Slot->UpdateSlot();
	}
	else if (InWeaponType == 1)
	{
		EquipedWeapon2Slot->WeaponSlotIndex = SlotIndex;
		EquipedWeapon2Slot->UpdateSlot();
	}
	else
	{
		return;
	}
}

void UInventoryWidget::UnEquipWeaponSlot(uint8 InWeaponType)
{
	if (InWeaponType == 0)
	{
		EquipedWeapon1Slot->WeaponSlotIndex = -1;
		EquipedWeapon1Slot->UnEquipUpdateSlot();
	}
	else if (InWeaponType == 1)
	{
		EquipedWeapon2Slot->WeaponSlotIndex = -1;
		EquipedWeapon2Slot->UnEquipUpdateSlot();
	}
	else
	{
		return;
	}
}

//void UInventoryWidget::UpdateConsumableSlots(UWrapBox* InConsumableTab, const TArray<FConsumableData>& InConsumableInventory)
//{
//	InConsumableTab->ClearChildren();
//
//	int i = 0;
//	for (const FConsumableData& ConsumableData : InConsumableInventory)
//	{
//		UConsumableSlotWidget* ConsumableSlot = CreateWidget<UConsumableSlotWidget>(GetWorld()->GetFirstPlayerController(), ConsumableSlotWidgetClass);
//		ConsumableSlotWidgets[i] = ConsumableSlot;
//		ConsumableSlot->ConsumableSlotData = ConsumableData;
//		ConsumableSlot->ConsumableSlotIndex = i;
//		ConsumableSlot->InventoryComponent = InventoryComponent.Get();
//		ConsumableSlot->ConsumableActionMenu = ConsumableActionMenuWidget;
//		ConsumableSlot->UpdateSlot();
//
//		InConsumableTab->AddChildToWrapBox(ConsumableSlot);
//
//		if (ConsumableData.IsEquiped)
//		{
//			InventoryComponent->QuickSlotArray[ConsumableData.QuickSlotIndex] = ConsumableData;
//		}
//
//		++i;
//	}
//}
