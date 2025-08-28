// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Weapon/WeaponBase.h"

#include "Other/Debug.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	WeaponType = EWeaponType::None;
	WeaponEquipState = EWeaponEquipStateType::None;
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}
