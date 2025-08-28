// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/WeaponSwitchingAnimNotify.h"

#include "Interface/AnimNotifyInterface.h"

void UWeaponSwitchingAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	check(MeshComp);

	AActor* MeshComponentOwner = MeshComp->GetOwner();
	if (MeshComponentOwner)
	{
		if (IAnimNotifyInterface* AnimNotifyInterface = Cast<IAnimNotifyInterface>(MeshComponentOwner))
		{
			AnimNotifyInterface->WeaponSwitchingEnd();
		}
	}
}
