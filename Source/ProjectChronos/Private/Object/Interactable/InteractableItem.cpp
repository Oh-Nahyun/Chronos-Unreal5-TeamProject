// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Interactable/InteractableItem.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

#include "Component/InventoryComponent.h"

#include "Other/Debug.h"

AInteractableItem::AInteractableItem()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	InteractableActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableActorMesh"));
	SetRootComponent(InteractableActorMesh);

	//// Initialize Variables
	ActorType = EActorType::InteractableObject;
	InteractableActorType = EInteractableActorType::DropItem;
	ItemType = EItemType::Material;
	////
}

void AInteractableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableItem::InteractionActorBeginOverlap()
{

}

void AInteractableItem::StartInteraction(UInventoryComponent* InInventoryComponent)
{
	if (InInventoryComponent)
	{
		InventoryComponent = InInventoryComponent;

		if (ItemType == EItemType::Weapon)
		{
			const FWeaponData& FoundedData = *ItemDataTableRowHandle.DataTable->FindRow<FWeaponData>(ItemDataTableRowHandle.RowName, TEXT("Cannot find data table"));

			if (FoundedData.ItemIcon.IsPending())
			{
				LoadWeaponIcon(FoundedData.ItemIcon);
			}
			else
			{
				bool IsGetItem = InventoryComponent->AddWeapon(FoundedData);
				if (IsGetItem)
				{
					InventoryComponent->UpdateWeaponTab();

					Destroy();
				}
				else
				{
					// 아이템을 획득할 수 없다는 UI 출력
					Debug::Print(TEXT("Not enough"), 5.f);
				}
			}
		}
		else if (ItemType == EItemType::Armor)
		{
			const FArmorData& FoundedData = *ItemDataTableRowHandle.DataTable->FindRow<FArmorData>(ItemDataTableRowHandle.RowName, TEXT("Cannot find data table"));

			if (FoundedData.ItemIcon.IsPending())
			{
				LoadArmorIcon(FoundedData.ItemIcon);
			}
			else
			{
				bool IsGetItem = InventoryComponent->AddArmor(FoundedData);
				if (IsGetItem)
				{
					InventoryComponent->UpdateArmorTab();

					Destroy();
				}
				else
				{
					// 아이템을 획득할 수 없다는 UI 출력
					Debug::Print(TEXT("Not enough"), 5.f);
				}
			}
		}
		else if (ItemType == EItemType::Consumable)
		{
			const FConsumableData& FoundedData = *ItemDataTableRowHandle.DataTable->FindRow<FConsumableData>(ItemDataTableRowHandle.RowName, TEXT("Cannot find data table"));

			if (FoundedData.ItemIcon.IsPending())
			{
				LoadConsumableIcon(FoundedData.ItemIcon);
			}
			else
			{
				bool IsGetItem = InventoryComponent->AddConsumable(FoundedData);
				if (IsGetItem)
				{
					InventoryComponent->UpdateConsumableTab();

					Destroy();
				}
				else
				{
					// 아이템을 획득할 수 없다는 UI 출력
					Debug::Print(TEXT("Not enough"), 5.f);
				}
			}
		}
		else if (ItemType == EItemType::Material)
		{
			const FItemData& FoundedData = *ItemDataTableRowHandle.DataTable->FindRow<FItemData>(ItemDataTableRowHandle.RowName, TEXT("Cannot find data table"));

			if (FoundedData.ItemIcon.IsPending())
			{
				LoadMaterialIcon(FoundedData.ItemIcon);
			}
			else
			{
				bool IsGetItem = InventoryComponent->AddMaterial(FoundedData);
				if (IsGetItem)
				{
					InventoryComponent->UpdateMaterialTab();

					Destroy();
				}
				else
				{
					// 아이템을 획득할 수 없다는 UI 출력
					Debug::Print(TEXT("Not enough"), 5.f);
				}
			}
		}
		else if (ItemType == EItemType::QuestItem)
		{
			const FItemData& FoundedData = *ItemDataTableRowHandle.DataTable->FindRow<FItemData>(ItemDataTableRowHandle.RowName, TEXT("Cannot find data table"));

			if (FoundedData.ItemIcon.IsPending())
			{
				LoadQuestItemIcon(FoundedData.ItemIcon);
			}
			else
			{
				bool IsGetItem = InventoryComponent->AddQuestItem(FoundedData);
				if (IsGetItem)
				{
					InventoryComponent->UpdateQuestItemTab();

					Destroy();
				}
				else
				{
					// 아이템을 획득할 수 없다는 UI 출력
					Debug::Print(TEXT("Not enough"), 5.f);
				}
			}
		}
		else
		{
			return;
		}
	}
}

void AInteractableItem::LoadWeaponIcon(TSoftObjectPtr<UTexture2D> InSoftObjectPtr)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	StreamableManager.RequestAsyncLoad(InSoftObjectPtr.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &AInteractableItem::LoadWeaponIconFinished));
}

void AInteractableItem::LoadWeaponIconFinished()
{
	const FWeaponData& FoundedData = *ItemDataTableRowHandle.DataTable->FindRow<FWeaponData>(ItemDataTableRowHandle.RowName, TEXT("Cannot find data table"));

	if (!FoundedData.ItemIcon.IsPending())
	{
		bool IsGetItem = InventoryComponent->AddWeapon(FoundedData);
		if (IsGetItem)
		{
			InventoryComponent->UpdateWeaponTab();

			Destroy();
		}
		else
		{
			// 아이템을 획득할 수 없다는 UI 출력
			Debug::Print(TEXT("Not enough"), 5.f);
		}
	}
}

void AInteractableItem::LoadArmorIcon(TSoftObjectPtr<UTexture2D> InSoftObjectPtr)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	StreamableManager.RequestAsyncLoad(InSoftObjectPtr.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &AInteractableItem::LoadArmorIconFinished));
}

void AInteractableItem::LoadArmorIconFinished()
{
	const FArmorData& FoundedData = *ItemDataTableRowHandle.DataTable->FindRow<FArmorData>(ItemDataTableRowHandle.RowName, TEXT("Cannot find data table"));

	if (!FoundedData.ItemIcon.IsPending())
	{
		bool IsGetItem = InventoryComponent->AddArmor(FoundedData);
		if (IsGetItem)
		{
			InventoryComponent->UpdateArmorTab();

			Destroy();
		}
		else
		{
			// 아이템을 획득할 수 없다는 UI 출력
			Debug::Print(TEXT("Not enough"), 5.f);
		}
	}
}

void AInteractableItem::LoadMaterialIcon(TSoftObjectPtr<UTexture2D> InSoftObjectPtr)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	StreamableManager.RequestAsyncLoad(InSoftObjectPtr.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &AInteractableItem::LoadMaterialIconFinished));
}

void AInteractableItem::LoadMaterialIconFinished()
{
	const FItemData& FoundedData = *ItemDataTableRowHandle.DataTable->FindRow<FItemData>(ItemDataTableRowHandle.RowName, TEXT("Cannot find data table"));

	if (!FoundedData.ItemIcon.IsPending())
	{
		bool IsGetItem = InventoryComponent->AddMaterial(FoundedData);
		if (IsGetItem)
		{
			InventoryComponent->UpdateMaterialTab();

			Destroy();
		}
		else
		{
			// 아이템을 획득할 수 없다는 UI 출력
			Debug::Print(TEXT("Not enough"), 5.f);
		}
	}
}

void AInteractableItem::LoadConsumableIcon(TSoftObjectPtr<UTexture2D> InSoftObjectPtr)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	StreamableManager.RequestAsyncLoad(InSoftObjectPtr.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &AInteractableItem::LoadConsumableIconFinished));
}

void AInteractableItem::LoadConsumableIconFinished()
{
	const FConsumableData& FoundedData = *ItemDataTableRowHandle.DataTable->FindRow<FConsumableData>(ItemDataTableRowHandle.RowName, TEXT("Cannot find data table"));

	if (!FoundedData.ItemIcon.IsPending())
	{
		bool IsGetItem = InventoryComponent->AddConsumable(FoundedData);
		if (IsGetItem)
		{
			InventoryComponent->UpdateConsumableTab();

			Destroy();
		}
		else
		{
			// 아이템을 획득할 수 없다는 UI 출력
			Debug::Print(TEXT("Not enough"), 5.f);
		}
	}
}

void AInteractableItem::LoadQuestItemIcon(TSoftObjectPtr<UTexture2D> InSoftObjectPtr)
{
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

	StreamableManager.RequestAsyncLoad(InSoftObjectPtr.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &AInteractableItem::LoadQuestItemIconFinished));
}

void AInteractableItem::LoadQuestItemIconFinished()
{
	const FItemData& FoundedData = *ItemDataTableRowHandle.DataTable->FindRow<FItemData>(ItemDataTableRowHandle.RowName, TEXT("Cannot find data table"));

	if (!FoundedData.ItemIcon.IsPending())
	{
		bool IsGetItem = InventoryComponent->AddQuestItem(FoundedData);
		if (IsGetItem)
		{
			InventoryComponent->UpdateQuestItemTab();

			Destroy();
		}
		else
		{
			// 아이템을 획득할 수 없다는 UI 출력
			Debug::Print(TEXT("Not enough"), 5.f);
		}
	}
}
