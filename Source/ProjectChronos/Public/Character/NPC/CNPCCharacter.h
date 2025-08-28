// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/InteractionInterface.h"
#include "CNPCCharacter.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class APlayerController;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROJECTCHRONOS_API ACNPCCharacter : public APawn, public IInteractionInterface
{
	GENERATED_BODY()

public:
	ACNPCCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	//virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


#pragma region Component
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

public:
	FORCEINLINE UCapsuleComponent* GetCapsuleComponent() const { return CapsuleComponent; }
	FORCEINLINE USkeletalMeshComponent* GetMesh() const { return MeshComponent; }
#pragma endregion


#pragma region Type
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC|Type", meta = (AllowPrivateAccess = "true"))
	EActorType ActorType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC|Type", meta = (AllowPrivateAccess = "true"))
	EInteractableActorType InteractableActorType;
#pragma endregion


#pragma region Variable
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC|Name", meta = (AllowPrivateAccess = "true"))
	FName NPCName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|ConversationPartnerController", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APlayerController> ConversationPartnerController;
#pragma endregion


#pragma region Widget
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC|Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> ConversationWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NPC|Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUserWidget> ConversationWidget;
#pragma endregion


#pragma region Interface
public:
	virtual void InteractionActorBeginOverlap() final;
	virtual EInteractableActorType GetInteractionActorType() const final { return InteractableActorType; }
	virtual void StartInteraction(UInventoryComponent* InInventoryComponent) final;
	virtual void StartInteraction(APlayerController* InPlayerController) final;
#pragma endregion


#pragma region Function
	UFUNCTION(BlueprintCallable)
	void EndConversation();

	UFUNCTION(BlueprintImplementableEvent)
	void CameraChange();

	UFUNCTION(BlueprintImplementableEvent)
	void StartConversation();
#pragma endregion
};
