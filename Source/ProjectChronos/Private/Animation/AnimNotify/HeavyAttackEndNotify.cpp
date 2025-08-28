// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/HeavyAttackEndNotify.h"

#include "Interface/AnimNotifyInterface.h"

void UHeavyAttackEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	check(MeshComp);

	AActor* MeshComponentOwner = MeshComp->GetOwner();
	if (MeshComponentOwner)
	{
		if (IAnimNotifyInterface* AnimNotifyInterface = Cast<IAnimNotifyInterface>(MeshComponentOwner))
		{
			AnimNotifyInterface->HeavyAttackEnd();
		}
	}
}
