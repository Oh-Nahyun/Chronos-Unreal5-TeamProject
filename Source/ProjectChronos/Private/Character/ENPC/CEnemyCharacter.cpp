// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ENPC/CEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "NavigationPath.h"

ACEnemyCharacter::ACEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ACEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnemyController = Cast<AAIController>(GetController());
}

void ACEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
