// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyState/CanNextComboNotifyState.h"

#include "Interface/AnimNotifyInterface.h"

void UCanNextComboNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	check(MeshComp);

	AActor* MeshComponentOwner = MeshComp->GetOwner();
	if (MeshComponentOwner)
	{
		if (IAnimNotifyInterface* AnimNotifyInterface = Cast<IAnimNotifyInterface>(MeshComponentOwner))
		{
			AnimNotifyInterface->ComboWindowStart();
		}
	}
}

void UCanNextComboNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	check(MeshComp);

	AActor* MeshComponentOwner = MeshComp->GetOwner();
	if (MeshComponentOwner)
	{
		if (IAnimNotifyInterface* AnimNotifyInterface = Cast<IAnimNotifyInterface>(MeshComponentOwner))
		{
			AnimNotifyInterface->ComboWindowEnd();
		}
	}
}
