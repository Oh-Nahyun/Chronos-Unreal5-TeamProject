// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/DashEndNotify.h"

#include "Interface/AnimNotifyInterface.h"

void UDashEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* MeshComponentOwner = MeshComp->GetOwner())
	{
		if (IAnimNotifyInterface* AnimNotifyInterface = Cast<IAnimNotifyInterface>(MeshComponentOwner))
		{
			AnimNotifyInterface->DashEnded();
		}
	}
}
