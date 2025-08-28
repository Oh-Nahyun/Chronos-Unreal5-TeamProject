// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/WeaponEquipAnimNotify.h"

#include "Interface/AnimNotifyInterface.h"

void UWeaponEquipAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	check(MeshComp);

	AActor* MeshComponentOwner = MeshComp->GetOwner();
	if (MeshComponentOwner)
	{
		if (IAnimNotifyInterface* AnimNotifyInterface = Cast<IAnimNotifyInterface>(MeshComponentOwner))
		{
			if (WeaponType == 1)
			{
				AnimNotifyInterface->EquipWeapon1();
			}
			else if (WeaponType == 2)
			{
				AnimNotifyInterface->EquipWeapon2();
			}
		}
	}
}
