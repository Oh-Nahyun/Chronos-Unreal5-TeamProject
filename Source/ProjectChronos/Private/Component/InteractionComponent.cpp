// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InteractionComponent.h"

#include "Interface/InteractionInterface.h"
#include "Character/CPlayerCharacter.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UInteractionComponent::InitializeOwner()
{
	if (OwningPlayerCharacter == nullptr)
	{
		OwningPlayerCharacter = CastChecked<ACPlayerCharacter>(GetOwner());
	}
}

void UInteractionComponent::DoInteraction(AActor* InInteractionActor)
{
	if (IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(InInteractionActor))
	{
		if (InteractionInterface->GetInteractionActorType() == EInteractableActorType::DropItem)
		{
			if (UInventoryComponent* InventoryComponentRef = OwningPlayerCharacter->GetInventoryComponent())
			{
				InteractionInterface->StartInteraction(InventoryComponentRef);
			}
		}
		else if (InteractionInterface->GetInteractionActorType() == EInteractableActorType::NPC)
		{
			if (OwningPlayerCharacter->PlayerCharacterController)
			{
				InteractionInterface->StartInteraction(OwningPlayerCharacter->PlayerCharacterController);
			}
		}
		else if (InteractionInterface->GetInteractionActorType() == EInteractableActorType::SavePoint)
		{

		}
		else if (InteractionInterface->GetInteractionActorType() == EInteractableActorType::Landscape)
		{

		}
	}
}
