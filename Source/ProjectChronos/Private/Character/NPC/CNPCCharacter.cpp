// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPC/CNPCCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"

#include "Other/Debug.h"

ACNPCCharacter::ACNPCCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	MeshComponent->SetupAttachment(CapsuleComponent);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.0f;
	CameraBoom->bUsePawnControlRotation = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//// Initialize Variables
	ActorType = EActorType::InteractableObject;
	InteractableActorType = EInteractableActorType::NPC;

	NPCName = FName();

	ConversationPartnerController = nullptr;

	ConversationWidgetClass = nullptr;
	ConversationWidget = nullptr;
	////
}

void ACNPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

//void ACNPCCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void ACNPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACNPCCharacter::InteractionActorBeginOverlap()
{

}

void ACNPCCharacter::StartInteraction(UInventoryComponent* InInventoryComponent)
{
	return;
}

void ACNPCCharacter::StartInteraction(APlayerController* InPlayerController)
{
	if (InPlayerController && ConversationPartnerController == nullptr)
	{
		ConversationPartnerController = InPlayerController;
	}

	if (ConversationWidget == nullptr)
	{
		ConversationWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), ConversationWidgetClass);

		FInputModeUIOnly ConversationInputMode;
		ConversationInputMode.SetWidgetToFocus(ConversationWidget->TakeWidget());
		ConversationPartnerController->SetInputMode(ConversationInputMode);
		ConversationPartnerController->FlushPressedKeys();
		ConversationPartnerController->bShowMouseCursor = true;

		ConversationWidget->AddToViewport();
	}
	else
	{
		FInputModeUIOnly ConversationInputMode;
		ConversationInputMode.SetWidgetToFocus(ConversationWidget->TakeWidget());
		ConversationPartnerController->SetInputMode(ConversationInputMode);
		ConversationPartnerController->FlushPressedKeys();
		ConversationPartnerController->bShowMouseCursor = true;

		ConversationWidget->AddToViewport();
	}

	StartConversation();
}

void ACNPCCharacter::EndConversation()
{
	CameraChange();

	ConversationPartnerController = nullptr;
}
