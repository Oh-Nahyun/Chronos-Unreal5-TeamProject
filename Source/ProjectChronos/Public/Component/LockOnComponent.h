// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnComponent.generated.h"

class ACPlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCHRONOS_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULockOnComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


#pragma region Owner
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACPlayerCharacter> OwningPlayerCharacter;

public:
	void InitializeOwner();
#pragma endregion

	
#pragma region Variable
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|LockOn", meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> AvailableActorsToLockOn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|LockOn", meta = (AllowPrivateAccess = "true"))
	AActor* CurrentLockedActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|LockOn", meta = (AllowPrivateAccess = "true"))
	float MaxLockOnDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|LockOn", meta = (AllowPrivateAccess = "true"))
	float MaxMaintainDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|LockOn", meta = (AllowPrivateAccess = "true"))
	float LockOnCameraRotationInterpSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|LockOn", meta = (AllowPrivateAccess = "true"))
	float LockOnCameraOffsetDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component|LockOn", meta = (AllowPrivateAccess = "true"))
	bool bShowPersistentDebugShape;

	UPROPERTY(EditDefaultsOnly, Category = "Component|LockOn")
	TArray<TEnumAsByte<EObjectTypeQuery>> SphereTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Component|LockOn")
	TEnumAsByte<ETraceTypeQuery> LineTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Component|LockOn")
	TEnumAsByte<ETraceTypeQuery> DistanceCheckTraceChannel;

	FTimerHandle WallCheckTimerHandle;
	FTimerHandle FinalCheckTimerHandle;

	uint8 WallCheckCount = 0;
#pragma endregion


#pragma region Function
public:
	bool DoLockOn();
	void DisableLockOn();

	void GetAvailableActorsToLockOn();
	AActor* GetNearestTargetFromCameraForwardVector();
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAVailableActors);
	void OnTargetLockOnTick(float DeltaTime);
	void SwitchTargetLockOn(int8 InDirection);
	void GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight);

	void WallCheck();
#pragma endregion
};
