// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Other/Enums.h"
#include "Interface/ActorTypeInterface.h"
#include "Interface/AnimNotifyInterface.h"
#include "Interface/DamageInterface.h"
#include "CPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAnimMontage;
class UStatusComponent;
class UInteractionComponent;
class UBoxComponent;
class UInventoryComponent;
class UWeaponComponent;
class AWeaponBase;
class ULockOnComponent;
class APlayerController;

UCLASS()
class PROJECTCHRONOS_API ACPlayerCharacter : public ACharacter, public IActorTypeInterface, public IAnimNotifyInterface, public IDamageInterface
{
	GENERATED_BODY()

public:
	ACPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void NotifyControllerChanged() override;
	virtual void PostInitializeComponents() override;
	virtual float CharacterTakeDamage(float Damage, AController* EventInstigator, AActor* DamageCauser, EDamageType InDamageType) final;


#pragma region Component
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStatusComponent> StatusComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInteractionComponent> InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> InteractionBoundaryBoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponComponent> WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Component", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ULockOnComponent> LockOnComponent;

public:
	FORCEINLINE UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE FVector GetFollowCameraLocation() const;
	FORCEINLINE FVector GetFollowCameraForwardVector() const;
#pragma endregion


#pragma region Input
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> PlayerInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> DashAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LeftClickAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LeftClickHoldAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RightClickAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Num1Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Num2Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Num3Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> Num4Action;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractionAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InventoryAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> TabAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LockOnAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> WheelScrollAction;

	float LeftClickStartTime = 0.f;
	float LeftClickEndTime = 0.f;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void PlayerJump();

	void Dash();
	void LeftClickStart();
	void LeftClickEnd();
	void LeftClickTriggered();
	void RightClickStart();
	void RightClickEnd();

	void Num1();
	void Num2();
	void Num3();
	void Num4();

	void Interaction();

	void OpenInventory();

	void Tab();

	void WheelClick();

	void WheelScroll(const FInputActionValue& Value);

	void SetMovementRotationRate(FVector2D& InVector);
#pragma endregion


#pragma region Type
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Type", meta = (AllowPrivateAccess = "true"))
	EActorType ActorType;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Type", meta = (AllowPrivateAccess = "true"))
	EStateType StateType;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Type", meta = (AllowPrivateAccess = "true"))
	TArray<uint8> WeaponTypes;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player|Type", meta = (AllowPrivateAccess = "true"))
	EWeaponType CurrentWeaponType;

public:
	FORCEINLINE const EStateType& GetStateType() { return StateType; }
#pragma endregion


#pragma region Interface
public:
	virtual EActorType GetActorType() const final { return ActorType; }

	virtual void DashEnded() final;
	virtual void DashInvincibleStart() final;
	virtual void DashInvincibleEnd() final;

public:
	virtual void ResetComboAttack() final;
	virtual void ComboStart() final;

	virtual void ComboWindowStart() final;
	virtual void ComboWindowEnd() final;

	virtual void HeavyAttackEnd() final;

public:
	virtual void RotationStartWhenAttack() final;
	virtual void RotationEndWhenAttack() final;

public:
	virtual void JustGuardStart() final;
	virtual void JustGuardEnd() final;

public:
	virtual void EquipWeapon1() final;
	virtual void EquipWeapon2() final;
	virtual void WeaponSwitchingEnd() final;
#pragma endregion


#pragma region Bind Delegate Function
	UFUNCTION()
	void OnPlayerCharacterLanded(const FHitResult& Hit);
#pragma endregion


#pragma region Animation Montage
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Montage", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DashMontage;
#pragma endregion


#pragma region Interaction
private:
	UFUNCTION()
	void OnInteractionBoudaryBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
#pragma endregion


#pragma region Attack
	void LightAttack();
	void HeavyAttack();
#pragma endregion


#pragma region Weapon
public:
	void EquipWeapon(EWeaponType InWeaponType, TSoftClassPtr<AWeaponBase> InWeaponClass, uint8 InWeaponSlotType);

	void UnEquipWeapon(uint8 InWeaponType);

	UFUNCTION(BlueprintImplementableEvent)
	void EquipWeaponRender();
#pragma endregion


#pragma region Guard
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Guard", meta = (AllowPrivateAccess = "true"))
	bool bIsJustGuard;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|WalkSpeed", meta = (AllowPrivateAccess = "true"))
	float GuardWalkSpeed;
#pragma endregion


#pragma region Invincible
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Invincible", meta = (AllowPrivateAccess = "true"))
	bool bIsInvincible;
#pragma endregion


#pragma region Zoom
public:
	UFUNCTION(BlueprintImplementableEvent)
	void ZoomIn();

	UFUNCTION(BlueprintImplementableEvent)
	void ZoomOut();

	UFUNCTION(BlueprintPure)
	bool CanZoomIn();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|WalkSpeed", meta = (AllowPrivateAccess = "true"))
	float ZoomedWalkSpeed;
#pragma endregion


#pragma region Lock On
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|LockOn", meta = (AllowPrivateAccess = "true"))
	bool bIsLockOnNow;

private:
	void LockOn();

public:
	void LockOnOff();
	void DisableLockOnTarget();
#pragma endregion


#pragma region Conversation
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Controller", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APlayerController> PlayerCharacterController;
#pragma endregion
};
