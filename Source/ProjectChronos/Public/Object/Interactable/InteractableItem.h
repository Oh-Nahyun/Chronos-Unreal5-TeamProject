// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/ActorTypeInterface.h"
#include "Interface/InteractionInterface.h"
#include "Other/ItemStruct.h"
#include "InteractableItem.generated.h"

class UStaticMeshComponent;
class UInventoryComponent;
class UDataTable;
class UTexture2D;

UCLASS()
class PROJECTCHRONOS_API AInteractableItem : public AActor, public IActorTypeInterface, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AInteractableItem();


protected:
	virtual void BeginPlay() override;


#pragma region Component
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InteractableActor|Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> InteractableActorMesh;
#pragma endregion


#pragma region Type
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InteractableActor|Type", meta = (AllowPrivateAccess = "true"))
	EActorType ActorType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "InteractableActor|Type", meta = (AllowPrivateAccess = "true"))
	EInteractableActorType InteractableActorType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractableActor|Type", meta = (AllowPrivateAccess = "true"))
	EItemType ItemType;
#pragma endregion


#pragma region Item Data
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractableActor|Data", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InteractableActor|Data", meta = (AllowPrivateAccess = "true"))
	FDataTableRowHandle ItemDataTableRowHandle;
#pragma endregion


#pragma region Interface
public:
	//// ActorTypeInterface
	virtual EActorType GetActorType() const final { return ActorType; }
	////

	//// InteractionInterface
	virtual void InteractionActorBeginOverlap() override;
	virtual EInteractableActorType GetInteractionActorType() const final { return InteractableActorType; }
	virtual void StartInteraction(UInventoryComponent* InInventoryComponent) override;
	virtual void StartInteraction(APlayerController* InPlayerController) final { return; }
	////
#pragma endregion


#pragma region Variable
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InteractableActor|Variable", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;
#pragma endregion


#pragma region Function
protected:
	//// Data load
	void LoadWeaponIcon(TSoftObjectPtr<UTexture2D> InSoftObjectPtr);
	void LoadWeaponIconFinished();

	void LoadArmorIcon(TSoftObjectPtr<UTexture2D> InSoftObjectPtr);
	void LoadArmorIconFinished();

	void LoadMaterialIcon(TSoftObjectPtr<UTexture2D> InSoftObjectPtr);
	void LoadMaterialIconFinished();

	void LoadConsumableIcon(TSoftObjectPtr<UTexture2D> InSoftObjectPtr);
	void LoadConsumableIconFinished();

	void LoadQuestItemIcon(TSoftObjectPtr<UTexture2D> InSoftObjectPtr);
	void LoadQuestItemIconFinished();
	////
#pragma endregion
};
