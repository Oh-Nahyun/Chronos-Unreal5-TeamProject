// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/LockOnComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Character/CPlayerCharacter.h"
#include "Interface/LockOnInterface.h"

#include "Other/Debug.h"

ULockOnComponent::ULockOnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	MaxLockOnDistance = 2000.f;
	MaxMaintainDistance = 1500.f;
	LockOnCameraRotationInterpSpeed = 5.f;
	LockOnCameraOffsetDistance = 10.f;
	bShowPersistentDebugShape = false;

	CurrentLockedActor = nullptr;
}

void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

}

void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (OwningPlayerCharacter->bIsLockOnNow)
	{
		OnTargetLockOnTick(DeltaTime);
	}
}

void ULockOnComponent::InitializeOwner()
{
	if (OwningPlayerCharacter == nullptr)
	{
		OwningPlayerCharacter = CastChecked<ACPlayerCharacter>(GetOwner());
	}
}

bool ULockOnComponent::DoLockOn()
{
	GetAvailableActorsToLockOn();

	if (AvailableActorsToLockOn.IsEmpty())
	{
		return false;
	}
	else
	{
		CurrentLockedActor = GetNearestTargetFromCameraForwardVector();

		if (ILockOnInterface* LockOnInterface = Cast<ILockOnInterface>(CurrentLockedActor))
		{
			LockOnInterface->DrawTargetLockWidget();
		}

		if (CurrentLockedActor)
		{
			GetWorld()->GetTimerManager().SetTimer(WallCheckTimerHandle, this, &ULockOnComponent::WallCheck, 1.f, true, 0.f);
		}

		return true;
	}
}

void ULockOnComponent::DisableLockOn()
{
	AvailableActorsToLockOn.Empty();

	if (ILockOnInterface* LockOnInterface = Cast<ILockOnInterface>(CurrentLockedActor))
	{
		LockOnInterface->DisableTargetLockWidget();
	}

	CurrentLockedActor = nullptr;

	if (GetWorld()->GetTimerManager().IsTimerActive(WallCheckTimerHandle))
	{
		GetWorld()->GetTimerManager().PauseTimer(WallCheckTimerHandle);
	}

	GetWorld()->GetTimerManager().ClearTimer(WallCheckTimerHandle);

	OwningPlayerCharacter->LockOnOff();
}

void ULockOnComponent::GetAvailableActorsToLockOn()
{
	// 벽 뒤에 있는 애들도 락 온?
	AvailableActorsToLockOn.Empty();

	TArray<FHitResult> SphereTraceHits;

	UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetOwner(),
		GetOwner()->GetActorLocation(),
		GetOwner()->GetActorLocation(),
		MaxLockOnDistance,
		SphereTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		SphereTraceHits,
		true
	);

	for (const FHitResult& SphereTraceHit : SphereTraceHits)
	{
		if (AActor* HitActor = SphereTraceHit.GetActor())
		{
			FHitResult LineTraceHit;
			UKismetSystemLibrary::LineTraceSingle(
				GetOwner(),
				GetOwner()->GetActorLocation(),
				SphereTraceHit.GetActor()->GetActorLocation(),
				LineTraceChannel,
				false,
				TArray<AActor*>(),
				bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
				LineTraceHit,
				true
			);

			if (LineTraceHit.bBlockingHit)
			{
				continue;
			}
			else
			{
				AvailableActorsToLockOn.AddUnique(HitActor);
			}
		}
	}
}

AActor* ULockOnComponent::GetNearestTargetFromCameraForwardVector()
{
	// 카메라 전방 벡터에서 가장 가까운 적을 타겟으로 하도록
	AActor* ClosestActor = nullptr;
	float MaxDotProduct = -1.f;

	for (AActor* TargetActor : AvailableActorsToLockOn)
	{
		FVector ToTargetDirectionVector = (TargetActor->GetActorLocation() - OwningPlayerCharacter->GetFollowCameraLocation()).GetSafeNormal();
		float Dot = FVector::DotProduct(OwningPlayerCharacter->GetFollowCameraForwardVector(), ToTargetDirectionVector);

		if (Dot > MaxDotProduct)
		{
			MaxDotProduct = Dot;
			ClosestActor = TargetActor;
		}
	}

	return ClosestActor;
}

AActor* ULockOnComponent::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAVailableActors)
{
	// 가장 가까운 액터
	float ClosestDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetOwner()->GetActorLocation(), InAVailableActors, ClosestDistance);
}

void ULockOnComponent::OnTargetLockOnTick(float DeltaTime)
{
	if (CurrentLockedActor == nullptr)
	{
		return;
	}

	if (OwningPlayerCharacter->StateType == EStateType::Dashing)
	{
		return;
	}

	// 대시 중이 아니라면
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
		GetOwner()->GetActorLocation(),
		CurrentLockedActor->GetActorLocation()
	);

	LookAtRot -= FRotator(LockOnCameraOffsetDistance, 0.f, 0.f);

	const FRotator CurrentControlRot = OwningPlayerCharacter->GetControlRotation();
	const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, LockOnCameraRotationInterpSpeed);

	OwningPlayerCharacter->GetController()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
}

void ULockOnComponent::SwitchTargetLockOn(int8 InDirection)
{
	// 기존 타겟의 UI 끄기
	if (ILockOnInterface* LockOnInterface = Cast<ILockOnInterface>(CurrentLockedActor))
	{
		LockOnInterface->DisableTargetLockWidget();
	}

	GetAvailableActorsToLockOn();

	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	AActor* NewTargetToLockOn = nullptr;

	GetAvailableActorsAroundTarget(ActorsOnLeft, ActorsOnRight);

	if (InDirection == 1)
	{
		// 왼쪽
		NewTargetToLockOn = GetNearestTargetFromAvailableActors(ActorsOnLeft);
	}
	else
	{
		// 오른쪽
		NewTargetToLockOn = GetNearestTargetFromAvailableActors(ActorsOnRight);
	}

	if (NewTargetToLockOn)
	{
		CurrentLockedActor = NewTargetToLockOn;
	}

	// 새 타겟의 UI 켜기
	if (ILockOnInterface* LockOnInterface = Cast<ILockOnInterface>(CurrentLockedActor))
	{
		LockOnInterface->DrawTargetLockWidget();
	}
}

void ULockOnComponent::GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight)
{
	if (!CurrentLockedActor || AvailableActorsToLockOn.IsEmpty())
	{
		return;
	}

	const FVector PlayerCharacterLocation = GetOwner()->GetActorLocation();
	const FVector PlayerCurrentNormalizedVector = (CurrentLockedActor->GetActorLocation() - PlayerCharacterLocation).GetSafeNormal();

	for (AActor* AvailableActor : AvailableActorsToLockOn)
	{
		if (!AvailableActor || AvailableActor == CurrentLockedActor)
		{
			continue;
		}

		const FVector PlayerToAvailableNormalizedVector = (AvailableActor->GetActorLocation() - PlayerCharacterLocation).GetSafeNormal();

		// 외적을 통해 락 온 가능한 액터가 현재 락 온 한 액터의 왼쪽에 있는 지 오른쪽에 있는 지 계산
		const FVector CrossResult = FVector::CrossProduct(PlayerCurrentNormalizedVector, PlayerToAvailableNormalizedVector);

		if (CrossResult.Z > 0.f)
		{
			// 락 온 가능한 액터가 현재 락 온 한 액터보다 오른쪽에 있는 경우이다.
			OutActorsOnRight.AddUnique(AvailableActor);
		}
		else
		{
			// 락 온 가능한 액터가 현재 락 온 한 액터보다 왼쪽에 있는 경우이다.
			OutActorsOnLeft.AddUnique(AvailableActor);
		}
	}
}

void ULockOnComponent::WallCheck()
{
	if (!CurrentLockedActor)
	{
		return;
	}

	FHitResult LineTraceHit;
	UKismetSystemLibrary::LineTraceSingle(
		GetOwner(),
		GetOwner()->GetActorLocation(),
		CurrentLockedActor->GetActorLocation(),
		LineTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		LineTraceHit,
		true
	);

	// 벽 체크
	if (LineTraceHit.bBlockingHit)
	{
		WallCheckCount += 1;

		if (WallCheckCount > 2)
		{
			GetWorld()->GetTimerManager().PauseTimer(WallCheckTimerHandle);
			DisableLockOn();
		}
	}
	else
	{
		WallCheckCount = 0;
	}

	// 거리 체크
	if (CurrentLockedActor)
	{
		float DistanceSquared = FVector::DistSquared2D(CurrentLockedActor->GetActorLocation(), GetOwner()->GetActorLocation());

		if (DistanceSquared > MaxMaintainDistance)
		{
			GetWorld()->GetTimerManager().PauseTimer(WallCheckTimerHandle);
			DisableLockOn();
		}
	}

	/*
	if (LineTraceHit.Distance > MaxMaintainDistance)
	{
		GetWorld()->GetTimerManager().PauseTimer(WallCheckTimerHandle);
		DisableLockOn();
	}
	*/
}
