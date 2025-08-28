// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InventoryComponent.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "Controller/CPlayerController.h"
#include "Character/CPlayerCharacter.h"
#include "Widget/Inventory/InventoryWidget.h"
#include "Widget/Inventory/Slot/WeaponSlotWidget.h"
#include "Widget/Inventory/Slot/ArmorSlotWidget.h"
#include "Widget/Inventory/Slot/ConsumableSlotWidget.h"

#include "Other/Debug.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	InventoryWidgetClass = nullptr;
	InventoryWidget = nullptr;

	InventorySize = 20;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("Inventory BeginPlay"));

	CreateInventoryWidget();
}

void UInventoryComponent::InitializeOwner(ACPlayerCharacter* InOwnerPlayerCharacter)
{
	if (InOwnerPlayerCharacter)
	{
		OwningPlayerCharacter = InOwnerPlayerCharacter;
	}
}

void UInventoryComponent::InitializeOwnerController(ACPlayerController* InOwningPlayerController)
{
	if (InOwningPlayerController)
	{
		OwningPlayerController = InOwningPlayerController;
	}
}

void UInventoryComponent::CreateInventoryWidget()
{
	if (!InventoryWidget)
	{
		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld()->GetFirstPlayerController(), InventoryWidgetClass);

		InventoryWidget->InventoryComponent = this;
	}

	InitializeInventorySlot();
}

void UInventoryComponent::OpenInventoryWidget()
{
	if (InventoryWidget)
	{
		FInputModeUIOnly InventoryInputMode;
		InventoryInputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
		OwningPlayerController->SetInputMode(InventoryInputMode);
		OwningPlayerController->FlushPressedKeys();
		OwningPlayerController->bShowMouseCursor = true;

		InventoryWidget->AddToViewport();
	}
}

void UInventoryComponent::InitializeInventorySlot()
{
	WeaponArray.Init(FWeaponData(), InventorySize);
	ArmorArray.Init(FArmorData(), InventorySize);
	ConsumableArray.Init(FConsumableData(), InventorySize);
	MaterialArray.Init(FItemData(), InventorySize);
	QuestItemArray.Init(FItemData(), InventorySize);

	InventoryWidget->WeaponSlotWidgets.Init(nullptr, InventorySize);
	InventoryWidget->ArmorSlotWidgets.Init(nullptr, InventorySize);
	InventoryWidget->ConsumableSlotWidgets.Init(nullptr, InventorySize);
	InventoryWidget->MaterialSlotWidgets.Init(nullptr, InventorySize);
	InventoryWidget->QuestItemSlotWidgets.Init(nullptr, InventorySize);

	QuickSlotArray.Init(-1, 4);
	ArmorEquipedSlotArray.Init(-1, 5);
	WeaponEquipedSlotArray.Init(-1, 2);

	if (InventoryWidget)
	{
		InventoryWidget->InitializeAllTabs();
	}
}

bool UInventoryComponent::AddWeapon(const FWeaponData& InWeaponData)
{
	int i = 0;
	for (const FWeaponData& ItemData : WeaponArray)
	{
		// 같은 아이템
		if (ItemData.ItemID == InWeaponData.ItemID)
		{
			int32 TotalQuantity = ItemData.ItemQuantity + InWeaponData.ItemQuantity;
			if (ItemData.StackSize >= TotalQuantity)
			{
				WeaponArray[i] = InWeaponData;
				WeaponArray[i].ItemQuantity = TotalQuantity;
				return true;
			}
			else
			{
				int j = 0;
				for (const FWeaponData& ItemData1 : WeaponArray)
				{
					if (ItemData1.ItemQuantity == 0)
					{
						WeaponArray[j] = InWeaponData;
						return true;
					}
					else if (ItemData1.ItemID == InWeaponData.ItemID)
					{
						int32 TotalQuantity1 = ItemData1.ItemQuantity + InWeaponData.ItemQuantity;
						if (ItemData1.StackSize >= TotalQuantity1)
						{
							WeaponArray[j] = InWeaponData;
							WeaponArray[j].ItemQuantity = TotalQuantity1;
							return true;
						}
						else
						{
							++j;
						}
					}
					else if (ItemData1.ItemID != InWeaponData.ItemID)
					{
						++j;
					}
				}

				return false;
			}
		}
		else
		{
			// 다른 아이템
			int k = 0;
			for (const FWeaponData& ItemData2 : WeaponArray)
			{
				int32 TotalQuantity2 = ItemData2.ItemQuantity + InWeaponData.ItemQuantity;

				if (ItemData2.ItemQuantity == 0)
				{
					WeaponArray[k] = InWeaponData;
					WeaponArray[k].ItemQuantity = TotalQuantity2;
					return true;
				}
				else if (ItemData2.ItemID == InWeaponData.ItemID)
				{
					if (ItemData2.StackSize >= TotalQuantity2)
					{
						WeaponArray[k] = InWeaponData;
						WeaponArray[k].ItemQuantity = TotalQuantity2;
						return true;
					}
					else
					{
						++k;
					}
				}
				else if (ItemData2.ItemID != InWeaponData.ItemID)
				{
					++k;
				}
			}
		}

		++i;
	}

	return false;
}

bool UInventoryComponent::AddArmor(const FArmorData& InArmorData)
{
	int i = 0;
	for (const FArmorData& ItemData : ArmorArray)
	{
		// 같은 아이템
		if (ItemData.ItemID == InArmorData.ItemID)
		{
			int32 TotalQuantity = ItemData.ItemQuantity + InArmorData.ItemQuantity;
			if (ItemData.StackSize >= TotalQuantity)
			{
				ArmorArray[i] = InArmorData;
				ArmorArray[i].ItemQuantity = TotalQuantity;
				return true;
			}
			else
			{
				int j = 0;
				for (const FArmorData& ItemData1 : ArmorArray)
				{
					if (ItemData1.ItemQuantity == 0)
					{
						ArmorArray[j] = InArmorData;
						return true;
					}
					else if (ItemData1.ItemID == InArmorData.ItemID)
					{
						int32 TotalQuantity1 = ItemData1.ItemQuantity + InArmorData.ItemQuantity;
						if (ItemData1.StackSize >= TotalQuantity1)
						{
							ArmorArray[j] = InArmorData;
							ArmorArray[j].ItemQuantity = TotalQuantity1;
							return true;
						}
						else
						{
							++j;
						}
					}
					else if (ItemData1.ItemID != InArmorData.ItemID)
					{
						++j;
					}
				}

				return false;
			}
		}
		else
		{
			// 다른 아이템
			int k = 0;
			for (const FArmorData& ItemData2 : ArmorArray)
			{
				int32 TotalQuantity2 = ItemData2.ItemQuantity + InArmorData.ItemQuantity;

				if (ItemData2.ItemQuantity == 0)
				{
					ArmorArray[k] = InArmorData;
					ArmorArray[k].ItemQuantity = TotalQuantity2;
					return true;
				}
				else if (ItemData2.ItemID == InArmorData.ItemID)
				{
					if (ItemData2.StackSize >= TotalQuantity2)
					{
						ArmorArray[k] = InArmorData;
						ArmorArray[k].ItemQuantity = TotalQuantity2;
						return true;
					}
					else
					{
						++k;
					}
				}
				else if (ItemData2.ItemID != InArmorData.ItemID)
				{
					++k;
				}
			}
		}

		++i;
	}

	return false;
}

bool UInventoryComponent::AddConsumable(const FConsumableData& InConsumableData)
{
	int i = 0;
	for (const FConsumableData& ItemData : ConsumableArray)
	{
		// 같은 아이템
		if (ItemData.ItemID == InConsumableData.ItemID)
		{
			int32 TotalQuantity = ItemData.ItemQuantity + InConsumableData.ItemQuantity;
			if (ItemData.StackSize >= TotalQuantity)
			{
				//ConsumableArray[i] = InConsumableData;
				ConsumableArray[i].ItemQuantity = TotalQuantity;
				return true;
			}
			else
			{
				int j = 0;
				for (const FConsumableData& ItemData1 : ConsumableArray)
				{
					if (ItemData1.ItemQuantity == 0)
					{
						ConsumableArray[j] = InConsumableData;
						return true;
					}
					else if (ItemData1.ItemID == InConsumableData.ItemID)
					{
						int32 TotalQuantity1 = ItemData1.ItemQuantity + InConsumableData.ItemQuantity;
						if (ItemData1.StackSize >= TotalQuantity1)
						{
							//ConsumableArray[j] = InConsumableData;
							ConsumableArray[j].ItemQuantity = TotalQuantity1;
							return true;
						}
						else
						{
							++j;
						}
					}
					else if (ItemData1.ItemID != InConsumableData.ItemID)
					{
						++j;
					}
				}

				return false;
			}
		}
		else
		{
			// 다른 아이템
			int k = 0;
			for (const FConsumableData& ItemData2 : ConsumableArray)
			{
				int32 TotalQuantity2 = ItemData2.ItemQuantity + InConsumableData.ItemQuantity;

				if (ItemData2.ItemQuantity == 0)
				{
					ConsumableArray[k] = InConsumableData;
					ConsumableArray[k].ItemQuantity = TotalQuantity2;
					return true;
				}
				else if (ItemData2.ItemID == InConsumableData.ItemID)
				{
					if (ItemData2.StackSize >= TotalQuantity2)
					{
						//ConsumableArray[k] = InConsumableData;
						ConsumableArray[k].ItemQuantity = TotalQuantity2;
						return true;
					}
					else
					{
						++k;
					}
				}
				else if (ItemData2.ItemID != InConsumableData.ItemID)
				{
					++k;
				}
			}
		}

		++i;
	}

	return false;
}

bool UInventoryComponent::AddMaterial(const FItemData& InItemData)
{
	int i = 0;
	for (const FItemData& ItemData : MaterialArray)
	{
		// 같은 아이템
		if (ItemData.ItemID == InItemData.ItemID)
		{
			int32 TotalQuantity = ItemData.ItemQuantity + InItemData.ItemQuantity;
			if (ItemData.StackSize >= TotalQuantity)
			{
				MaterialArray[i] = InItemData;
				MaterialArray[i].ItemQuantity = TotalQuantity;
				return true;
			}
			else
			{
				int j = 0;
				for (const FItemData& ItemData1 : MaterialArray)
				{
					if (ItemData1.ItemQuantity == 0)
					{
						MaterialArray[j] = InItemData;
						return true;
					}
					else if (ItemData1.ItemID == InItemData.ItemID)
					{
						int32 TotalQuantity1 = ItemData1.ItemQuantity + InItemData.ItemQuantity;
						if (ItemData1.StackSize >= TotalQuantity1)
						{
							MaterialArray[j] = InItemData;
							MaterialArray[j].ItemQuantity = TotalQuantity1;
							return true;
						}
						else
						{
							++j;
						}
					}
					else if (ItemData1.ItemID != InItemData.ItemID)
					{
						++j;
					}
				}

				return false;
			}
		}
		else
		{
			// 다른 아이템
			int k = 0;
			for (const FItemData& ItemData2 : MaterialArray)
			{
				int32 TotalQuantity2 = ItemData2.ItemQuantity + InItemData.ItemQuantity;

				if (ItemData2.ItemQuantity == 0)
				{
					MaterialArray[k] = InItemData;
					MaterialArray[k].ItemQuantity = TotalQuantity2;
					return true;
				}
				else if (ItemData2.ItemID == InItemData.ItemID)
				{
					if (ItemData2.StackSize >= TotalQuantity2)
					{
						MaterialArray[k] = InItemData;
						MaterialArray[k].ItemQuantity = TotalQuantity2;
						return true;
					}
					else
					{
						++k;
					}
				}
				else if (ItemData2.ItemID != InItemData.ItemID)
				{
					++k;
				}
			}
		}

		++i;
	}

	return false;
}

bool UInventoryComponent::AddQuestItem(const FItemData& InQuestItemData)
{
	int i = 0;
	for (const FItemData& QuestItemData : QuestItemArray)
	{
		// 같은 아이템
		if (QuestItemData.ItemID == InQuestItemData.ItemID)
		{
			int32 TotalQuantity = QuestItemData.ItemQuantity + InQuestItemData.ItemQuantity;
			if (QuestItemData.StackSize >= TotalQuantity)
			{
				QuestItemArray[i] = InQuestItemData;
				QuestItemArray[i].ItemQuantity = TotalQuantity;
				return true;
			}
			else
			{
				int j = 0;
				for (const FItemData& QuestItemData1 : QuestItemArray)
				{
					if (QuestItemData1.ItemQuantity == 0)
					{
						QuestItemArray[j] = InQuestItemData;
						return true;
					}
					else if (QuestItemData1.ItemID == InQuestItemData.ItemID)
					{
						int32 TotalQuantity1 = QuestItemData1.ItemQuantity + InQuestItemData.ItemQuantity;
						if (QuestItemData1.StackSize >= TotalQuantity1)
						{
							QuestItemArray[j] = InQuestItemData;
							QuestItemArray[j].ItemQuantity = TotalQuantity1;
							return true;
						}
						else
						{
							++j;
						}
					}
					else if (QuestItemData1.ItemID != InQuestItemData.ItemID)
					{
						++j;
					}
				}

				return false;
			}
		}
		else
		{
			// 다른 아이템
			int k = 0;
			for (const FItemData& QuestItemData2 : QuestItemArray)
			{
				int32 TotalQuantity2 = QuestItemData2.ItemQuantity + InQuestItemData.ItemQuantity;

				if (QuestItemData2.ItemQuantity == 0)
				{
					QuestItemArray[k] = InQuestItemData;
					QuestItemArray[k].ItemQuantity = TotalQuantity2;
					return true;
				}
				else if (QuestItemData2.ItemID == InQuestItemData.ItemID)
				{
					if (QuestItemData2.StackSize >= TotalQuantity2)
					{
						QuestItemArray[k] = InQuestItemData;
						QuestItemArray[k].ItemQuantity = TotalQuantity2;
						return true;
					}
					else
					{
						++k;
					}
				}
				else if (QuestItemData2.ItemID != InQuestItemData.ItemID)
				{
					++k;
				}
			}
		}

		++i;
	}

	return false;
}

void UInventoryComponent::UpdateWeaponTab()
{
	if (InventoryWidget)
	{
		InventoryWidget->UpdateWeaponTab();
	}
}

void UInventoryComponent::UpdateArmorTab()
{
	if (InventoryWidget)
	{
		InventoryWidget->UpdateArmorTab();
	}
}

void UInventoryComponent::UpdateConsumableTab()
{
	if (InventoryWidget)
	{
		InventoryWidget->UpdateConsumableTab();
	}
}

void UInventoryComponent::UpdateMaterialTab()
{
	if (InventoryWidget)
	{
		InventoryWidget->UpdateMaterialTab();
	}
}

void UInventoryComponent::UpdateQuestItemTab()
{
	if (InventoryWidget)
	{
		InventoryWidget->UpdateQuestItemTab();
	}
}

void UInventoryComponent::UseConsumable(int32 InSlotIndex)
{
	int32 NewQuantity = ConsumableArray[InSlotIndex].ItemQuantity - 1;
	//int32 SlotStackSize = ConsumableArray[InSlotIndex].StackSize;
	if (NewQuantity == 0)
	{
		int32 QuickSlotIndex = ConsumableArray[InSlotIndex].QuickSlotIndex;
		QuickSlotArray[QuickSlotIndex] = -1;

		ConsumableArray[InSlotIndex] = FConsumableData();
		//ConsumableArray[InSlotIndex].StackSize = SlotStackSize;
	}
	else
	{
		ConsumableArray[InSlotIndex].ItemQuantity = NewQuantity;
	}

	UpdateConsumableTab();
}

void UInventoryComponent::DropItem(uint8 InItemType, int32 InSlotIndex)
{
	if (InItemType == 1)
	{
		//int32 SlotStackSize = WeaponArray[InSlotIndex].StackSize;
		WeaponArray[InSlotIndex] = FWeaponData();
		//WeaponArray[InSlotIndex].StackSize = SlotStackSize;

		UpdateWeaponTab();
	}
	else if (InItemType == 2)
	{
		//int32 SlotStackSize = ArmorArray[InSlotIndex].StackSize;
		ArmorArray[InSlotIndex] = FArmorData();
		//ArmorArray[InSlotIndex].StackSize = SlotStackSize;

		UpdateArmorTab();
	}
	else if (InItemType == 3)
	{
		//int32 SlotStackSize = ConsumableArray[InSlotIndex].StackSize;
		ConsumableArray[InSlotIndex] = FConsumableData();
		//ConsumableArray[InSlotIndex].StackSize = SlotStackSize;

		UpdateConsumableTab();
	}
	else if (InItemType == 4)
	{
		//int32 SlotStackSize = MaterialArray[InSlotIndex].StackSize;
		MaterialArray[InSlotIndex] = FItemData();
		//MaterialArray[InSlotIndex].StackSize = SlotStackSize;

		UpdateMaterialTab();
	}
	else if (InItemType == 5)
	{
		//int32 SlotStackSize = QuestItemArray[InSlotIndex].StackSize;
		QuestItemArray[InSlotIndex] = FItemData();
		//QuestItemArray[InSlotIndex].StackSize = SlotStackSize;

		UpdateQuestItemTab();
	}
	else
	{
		return;
	}
}

void UInventoryComponent::EquipConsumableInQuickSlot(uint8 InQuickSlotIndex, int32 InSlotIndex)
{
	// 퀵슬롯 비어있음
	if (QuickSlotArray[InQuickSlotIndex] == -1)
	{
		// 이 아이템은 퀵슬롯에 처음 등록하는 아이템
		if (ConsumableArray[InSlotIndex].QuickSlotIndex == -1)
		{
			QuickSlotArray[InQuickSlotIndex] = InSlotIndex;
			ConsumableArray[InSlotIndex].QuickSlotIndex = InQuickSlotIndex;
			ConsumableArray[InSlotIndex].IsEquiped = true;
			InventoryWidget->ConsumableSlotWidgets[InSlotIndex]->EquipOnQuickSlot();

			return;
		}
		// 이 아이템은 다른 퀵슬롯에 등록해 있다가 새 퀵슬롯으로 옮기려고 하는 아이템
		else
		{
			// 전에 있던 위치의 퀵슬롯 초기화
			uint8 Index = ConsumableArray[InSlotIndex].QuickSlotIndex;
			QuickSlotArray[Index] = -1;

			// 새 퀵슬롯으로 옮기기
			QuickSlotArray[InQuickSlotIndex] = InSlotIndex;
			ConsumableArray[InSlotIndex].QuickSlotIndex = InQuickSlotIndex;

			return;
		}
	}
	// 퀵슬롯에 뭔가 등록되어 있음
	else
	{
		// 퀵슬롯에 처음 등록하는 아이템
		if (ConsumableArray[InSlotIndex].QuickSlotIndex == -1)
		{
			// 먼저 원래 등록되어 있던 아이템 등록 해제
			uint8 InventorySlotIndex = QuickSlotArray[InQuickSlotIndex];
			ConsumableArray[InventorySlotIndex].QuickSlotIndex = -1;
			ConsumableArray[InventorySlotIndex].IsEquiped = false;
			InventoryWidget->ConsumableSlotWidgets[InventorySlotIndex]->UnEquipOnQuickSlot();
			QuickSlotArray[InQuickSlotIndex] = -1;

			// 새 아이템 등록
			QuickSlotArray[InQuickSlotIndex] = InSlotIndex;
			ConsumableArray[InSlotIndex].QuickSlotIndex = InQuickSlotIndex;
			ConsumableArray[InSlotIndex].IsEquiped = true;
			InventoryWidget->ConsumableSlotWidgets[InSlotIndex]->EquipOnQuickSlot();

			return;
		}
		// 원래 있던 칸에 또 등록하려는 경우
		else if (ConsumableArray[InSlotIndex].QuickSlotIndex == InQuickSlotIndex)
		{
			return;
		}
		// 다른 퀵슬롯에 등록해 있다가 새 퀵슬롯으로 옮기려고 하는 아이템
		else
		{
			// 전에 있던 위치의 퀵슬롯 초기화
			uint8 Index = ConsumableArray[InSlotIndex].QuickSlotIndex;
			QuickSlotArray[Index] = -1;

			// 원래 등록되어 있던 아이템 등록 해제
			uint8 InventorySlotIndex = QuickSlotArray[InQuickSlotIndex];
			ConsumableArray[InventorySlotIndex].QuickSlotIndex = -1;
			ConsumableArray[InventorySlotIndex].IsEquiped = false;
			InventoryWidget->ConsumableSlotWidgets[InventorySlotIndex]->UnEquipOnQuickSlot();
			QuickSlotArray[InQuickSlotIndex] = -1;

			// 새 아이템 등록
			QuickSlotArray[InQuickSlotIndex] = InSlotIndex;
			ConsumableArray[InSlotIndex].QuickSlotIndex = InQuickSlotIndex;

			return;
		}
	}
}

void UInventoryComponent::EquipArmor(int32 InSlotIndex)
{
	bool IsAlreadyEquip = ArmorArray[InSlotIndex].IsEquiped;
	if (IsAlreadyEquip)
	{
		Debug::Print(TEXT("Already equip same Armor"), 3.f);
		return;
	}

	ArmorArray[InSlotIndex].IsEquiped = true;
	InventoryWidget->ArmorSlotWidgets[InSlotIndex]->EquipOnSlot();

	// TODO
	// 방어구의 ID로 데이터 테이블에서 스탯 수치를 찾아 스탯을 더해줘야 할 듯
	// 같은 종류의 방어구끼리 장착할 땐 원래 입고 있던 방어구 해제하고 장착하도록
	// ex) 기존 머리 장비 -> 새 머리 장비 착용 경우엔 기존 머리 장비를 해제하고 새 머리 장비를 착용하도록 로직 수정하기

	EArmorType ArmorType = ArmorArray[InSlotIndex].ArmorType;
	if (ArmorType == EArmorType::Head)
	{
		// 아무 것도 장착되어 있지 않을 때
		if (ArmorEquipedSlotArray[0] == -1)
		{
			ArmorEquipedSlotArray[0] = InSlotIndex;
			InventoryWidget->UpdateEquipedArmorSlot(0, InSlotIndex);
		}
		// 이미 같은 부위가 장착되어 있을 때
		else
		{
			int32 SlotIndex = ArmorEquipedSlotArray[0];
			UnEquipArmor(0, SlotIndex);

			ArmorEquipedSlotArray[0] = InSlotIndex;
			InventoryWidget->UpdateEquipedArmorSlot(0, InSlotIndex);
		}

		// 스탯 더해주기
	}
	else if (ArmorType == EArmorType::Chest)
	{
		if (ArmorEquipedSlotArray[1] == -1)
		{
			ArmorEquipedSlotArray[1] = InSlotIndex;
			InventoryWidget->UpdateEquipedArmorSlot(1, InSlotIndex);
		}
		else
		{
			int32 SlotIndex = ArmorEquipedSlotArray[1];
			UnEquipArmor(1, SlotIndex);

			ArmorEquipedSlotArray[1] = InSlotIndex;
			InventoryWidget->UpdateEquipedArmorSlot(1, InSlotIndex);
		}

		// 스탯 더해주기
	}
	else if (ArmorType == EArmorType::Leg)
	{
		if (ArmorEquipedSlotArray[2] == -1)
		{
			ArmorEquipedSlotArray[2] = InSlotIndex;
			InventoryWidget->UpdateEquipedArmorSlot(2, InSlotIndex);
		}
		else
		{
			int32 SlotIndex = ArmorEquipedSlotArray[2];
			UnEquipArmor(2, SlotIndex);

			ArmorEquipedSlotArray[2] = InSlotIndex;
			InventoryWidget->UpdateEquipedArmorSlot(2, InSlotIndex);
		}

		// 스탯 더해주기
	}
	else if (ArmorType == EArmorType::Shoes)
	{
		if (ArmorEquipedSlotArray[3] == -1)
		{
			ArmorEquipedSlotArray[3] = InSlotIndex;
			InventoryWidget->UpdateEquipedArmorSlot(3, InSlotIndex);
		}
		else
		{
			int32 SlotIndex = ArmorEquipedSlotArray[3];
			UnEquipArmor(3, SlotIndex);

			ArmorEquipedSlotArray[3] = InSlotIndex;
			InventoryWidget->UpdateEquipedArmorSlot(3, InSlotIndex);
		}

		// 스탯 더해주기
	}
	else if (ArmorType == EArmorType::Accessories)
	{
		if (ArmorEquipedSlotArray[4] == -1)
		{
			ArmorEquipedSlotArray[4] = InSlotIndex;
			InventoryWidget->UpdateEquipedArmorSlot(4, InSlotIndex);
		}
		else
		{
			int32 SlotIndex = ArmorEquipedSlotArray[4];
			UnEquipArmor(4, SlotIndex);

			ArmorEquipedSlotArray[4] = InSlotIndex;
			InventoryWidget->UpdateEquipedArmorSlot(4, InSlotIndex);
		}

		// 스탯 더해주기
	}
	else
	{
		return;
	}
}

void UInventoryComponent::UnEquipArmor(uint8 InArmorType, int32 InSlotIndex)
{
	ArmorArray[InSlotIndex].IsEquiped = false;
	InventoryWidget->ArmorSlotWidgets[InSlotIndex]->UnEquipOnSlot();

	ArmorEquipedSlotArray[InArmorType] = -1;
	InventoryWidget->UnEquipArmorSlot(InArmorType);

	// 캐릭터 스탯 빼주기
}

void UInventoryComponent::EquipWeapon(int32 InSlotIndex)
{
	if (WeaponEquipedSlotArray[0] == InSlotIndex)
	{
		Debug::Print(TEXT("Already equip same weapon"), 3.f);
		return;
	}

	if (WeaponEquipedSlotArray[1] == InSlotIndex)
	{
		Debug::Print(TEXT("Already equip same weapon"), 3.f);
		return;
	}

	if (WeaponArray[InSlotIndex].IsEquiped)
	{
		Debug::Print(TEXT("Already equip same weapon"), 3.f);
		return;
	}

	EWeaponSlotType WeaponSlotType = WeaponArray[InSlotIndex].WeaponSlotType;
	EWeaponType WeaponType = WeaponArray[InSlotIndex].WeaponType;

	if (WeaponSlotType == EWeaponSlotType::Switching1)
	{
		// 슬롯에 다른 무기가 장착된 상태로 새 무기를 장착할 때
		if (WeaponEquipedSlotArray[0] != -1)
		{
			// 기존 무기 장착 해제
			int32 SlotIndex = WeaponEquipedSlotArray[0];
			UnEquipWeapon(0, SlotIndex);

			// 새 무기 장착
			InventoryWidget->UpdateEquipedWeaponSlot(0, InSlotIndex);

			OwningPlayerCharacter->EquipWeapon(WeaponType, WeaponArray[InSlotIndex].WeaponClass, 0);

			WeaponArray[InSlotIndex].IsEquiped = true;
			WeaponEquipedSlotArray[0] = InSlotIndex;
			InventoryWidget->WeaponSlotWidgets[InSlotIndex]->EquipOnSlot();
		}
		// 슬롯에 아무 것도 없는 상태에서 장착할 때
		else
		{
			InventoryWidget->UpdateEquipedWeaponSlot(0, InSlotIndex);

			OwningPlayerCharacter->EquipWeapon(WeaponType, WeaponArray[InSlotIndex].WeaponClass, 0);

			WeaponArray[InSlotIndex].IsEquiped = true;
			WeaponEquipedSlotArray[0] = InSlotIndex;
			InventoryWidget->WeaponSlotWidgets[InSlotIndex]->EquipOnSlot();
		}
	}
	else if (WeaponSlotType == EWeaponSlotType::Switching2)
	{
		InventoryWidget->UpdateEquipedWeaponSlot(1, InSlotIndex);

		OwningPlayerCharacter->EquipWeapon(WeaponType, WeaponArray[InSlotIndex].WeaponClass, 1);

		WeaponArray[InSlotIndex].IsEquiped = true;
		WeaponEquipedSlotArray[1] = InSlotIndex;
		InventoryWidget->WeaponSlotWidgets[InSlotIndex]->EquipOnSlot();

		// 스탯 더해주기
	}
	else
	{
		return;
	}
}

void UInventoryComponent::UnEquipWeapon(uint8 InWeaponType, int32 InSlotIndex)
{
	WeaponArray[InSlotIndex].IsEquiped = false;
	InventoryWidget->WeaponSlotWidgets[InSlotIndex]->UnEquipOnSlot();

	WeaponEquipedSlotArray[InWeaponType] = -1;
	InventoryWidget->UnEquipWeaponSlot(InWeaponType);

	OwningPlayerCharacter->UnEquipWeapon(InWeaponType);

	// 스탯 빼주기
}

void UInventoryComponent::UseQuickSlot(uint8 InQuickSlotIndex)
{
	// 아무 것도 등록되지 않은 슬롯이라면 사용 X
	if (QuickSlotArray[InQuickSlotIndex] == -1)
	{
		Debug::Print(TEXT("Nothing in slot"), 3.f);
		return;
	}

	// 0개 라면 사용 X
	int32 SlotIndex = QuickSlotArray[InQuickSlotIndex];
	int32 Quantity = ConsumableArray[SlotIndex].ItemQuantity;
	if (Quantity == 0)
	{
		Debug::Print(TEXT("Empty"), 3.f);
		return;
	}

	UseConsumable(SlotIndex);
}
