// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Other/Enums.h"
#include "InteractionInterface.generated.h"

class UInventoryComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};
/**
 * 
 */
class PROJECTCHRONOS_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void InteractionActorBeginOverlap() = 0;
	virtual EInteractableActorType GetInteractionActorType() const = 0;
	virtual void StartInteraction(UInventoryComponent* InInventoryComponent) = 0;
	virtual void StartInteraction(APlayerController* InPlayerController) = 0;
};
