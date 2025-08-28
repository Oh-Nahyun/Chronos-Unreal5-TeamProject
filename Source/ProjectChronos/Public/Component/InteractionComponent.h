// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class ACPlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCHRONOS_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

protected:
	virtual void BeginPlay() override;


#pragma region Owner
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Owner", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACPlayerCharacter> OwningPlayerCharacter;

public:
	void InitializeOwner();
#pragma endregion


#pragma region Interaction
public:
	void DoInteraction(AActor* InInteractionActor);
#pragma endregion
};
