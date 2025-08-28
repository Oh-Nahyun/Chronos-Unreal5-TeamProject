// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CPlayerCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

#include "Controller/CPlayerController.h"
#include "Component/StatusComponent.h"
#include "Component/InteractionComponent.h"
#include "Component/InventoryComponent.h"
#include "Component/WeaponComponent.h"
#include "Component/LockOnComponent.h"

#include "Other/Debug.h"

ACPlayerCharacter::ACPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 92.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	UCharacterMovementComponent* CharacterMovementComp = GetCharacterMovement();

	CharacterMovementComp->bOrientRotationToMovement = true;
	CharacterMovementComp->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	CharacterMovementComp->JumpZVelocity = 700.f;
	CharacterMovementComp->AirControl = 0.35f;
	CharacterMovementComp->MaxWalkSpeed = 500.f;
	CharacterMovementComp->MinAnalogWalkSpeed = 20.f;
	CharacterMovementComp->BrakingDecelerationWalking = 2000.f;
	CharacterMovementComp->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//// Components
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));

	InteractionBoundaryBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBoundaryComponent"));
	InteractionBoundaryBoxComponent->SetupAttachment(RootComponent);
	//InteractionBoundaryBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACPlayerCharacter::OnInteractionBoudaryBoxBeginOverlap);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));

	LockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOnComponent"));
	////

	ActorType = EActorType::PlayerCharacter;
	StateType = EStateType::Idle;
	CurrentWeaponType = EWeaponType::None;
	bIsJustGuard = false;
	bIsInvincible = false;

	GuardWalkSpeed = 180.f;
	ZoomedWalkSpeed = 250.f;

	bIsLockOnNow = false;

	PlayerCharacterController = nullptr;
}

void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
}

void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent"));

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACPlayerCharacter::PlayerJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &ACPlayerCharacter::Dash);
		//EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &ACPlayerCharacter::LeftClick);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &ACPlayerCharacter::LeftClickStart);
		EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::LeftClickEnd);
		EnhancedInputComponent->BindAction(LeftClickHoldAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::LeftClickTriggered);

		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Started, this, &ACPlayerCharacter::RightClickStart);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::RightClickEnd);
		EnhancedInputComponent->BindAction(RightClickAction, ETriggerEvent::Canceled, this, &ACPlayerCharacter::RightClickEnd);

		EnhancedInputComponent->BindAction(Num1Action, ETriggerEvent::Started, this, &ACPlayerCharacter::Num1);
		EnhancedInputComponent->BindAction(Num2Action, ETriggerEvent::Started, this, &ACPlayerCharacter::Num2);
		EnhancedInputComponent->BindAction(Num3Action, ETriggerEvent::Started, this, &ACPlayerCharacter::Num3);
		EnhancedInputComponent->BindAction(Num4Action, ETriggerEvent::Started, this, &ACPlayerCharacter::Num4);

		EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &ACPlayerCharacter::Interaction);

		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &ACPlayerCharacter::OpenInventory);

		EnhancedInputComponent->BindAction(TabAction, ETriggerEvent::Started, this, &ACPlayerCharacter::Tab);

		EnhancedInputComponent->BindAction(LockOnAction, ETriggerEvent::Started, this, &ACPlayerCharacter::WheelClick);
		EnhancedInputComponent->BindAction(WheelScrollAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::WheelScroll);
	}
}

void ACPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (ACPlayerController* PlayerControllerRef = CastChecked<ACPlayerController>(NewController))
	{
		InventoryComponent->InitializeOwnerController(PlayerControllerRef);

		PlayerCharacterController = PlayerControllerRef;
	}
}

void ACPlayerCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			EnhancedInputSubsystem->AddMappingContext(PlayerInputMappingContext, 0);
		}
	}
}

void ACPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UE_LOG(LogTemp, Warning, TEXT("PostInitializeComponents"));

	//// Component Initialize Section
	StatusComponent->InitStatusData();

	InteractionComponent->InitializeOwner();

	InventoryComponent->InitializeOwner(this);

	WeaponComponent->InitializeOwner();

	LockOnComponent->InitializeOwner();
	////

	WeaponTypes.Init(0, 2);

	//// Binding Section
	LandedDelegate.AddDynamic(this, &ACPlayerCharacter::OnPlayerCharacterLanded);
	InteractionBoundaryBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACPlayerCharacter::OnInteractionBoudaryBoxBeginOverlap);
	////
}

float ACPlayerCharacter::CharacterTakeDamage(float Damage, AController* EventInstigator, AActor* DamageCauser, EDamageType InDamageType)
{
	if (!EventInstigator || !DamageCauser)
	{
		return 0.0f;
	}

	if (bIsInvincible)
	{
		return 0.0f;
	}

	if (InDamageType == EDamageType::Normal)
	{
		if (StateType == EStateType::Guarding)
		{
			if (bIsJustGuard)
			{
				// 저스트 가드 성공
				return 0.0f;
			}
			else
			{
				// 일반 가드 성공
				StatusComponent->GuardSuccess();
				return 0.0f;
			}
		}
		else
		{
			// 가드 안 한 상태로 그냥 맞았을 때
			// 데미지 적용
			StatusComponent->TakeDamage(Damage);
			return 0.0f;
		}
	}
	else if (InDamageType == EDamageType::Hard || InDamageType == EDamageType::Area)
	{
		// 강공격과 범위 공격은 막기가 불가능
		// 대쉬로 회피하는 것만 가능
		// 맞으면 그냥 데미지 받아야 함
		StatusComponent->TakeDamage(Damage);
		return 0.0f;
	}
	else if (InDamageType == EDamageType::Range)
	{
		if (bIsJustGuard)
		{
			// 원거리 공격 저스트 가드 성공
			return 0.0f;
		}
		else
		{
			// 저스트 가드로만 막을 수 있음
			StatusComponent->TakeDamage(Damage);
			return 0.0f;
		}
	}
	else
	{
		return 0.0f;
	}
}

FVector ACPlayerCharacter::GetFollowCameraLocation() const
{
	return FollowCamera->GetComponentLocation();
}

FVector ACPlayerCharacter::GetFollowCameraForwardVector() const
{
	return FollowCamera->GetForwardVector();
}

void ACPlayerCharacter::Move(const FInputActionValue& Value)
{
	if (StateType == EStateType::HeavyAttackCharging || StateType == EStateType::Dashing || StateType == EStateType::HeavyAttacking || StateType == EStateType::Guarding)
	{
		return;
	}

	//Debug::Print(TEXT("Move"), 3.f);

	if (Controller != nullptr)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		if (StateType != EStateType::ZoomIn)
		{
			SetMovementRotationRate(MovementVector);
		}

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACPlayerCharacter::Look(const FInputActionValue& Value)
{
	if (bIsLockOnNow)
	{
		return;
	}

	if (Controller != nullptr)
	{
		FVector2D LookAxisVector = Value.Get<FVector2D>();

		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACPlayerCharacter::PlayerJump()
{
	// 대쉬 중 점프 불가능, 점프 중 중복으로 점프 불가능
	if (StateType == EStateType::Dashing || StateType == EStateType::Jumping || StateType == EStateType::HeavyAttacking || StateType == EStateType::Switching || StateType == EStateType::ZoomIn)
	{
		return;
	}

	// 스태미너가 0이거나 소모치만큼 있지 않다면 사용 불가능
	if (!StatusComponent->CanDoAction(EActionType::Jump))
	{
		return;
	}

	if (StateType == EStateType::Guarding)
	{
		StateType = EStateType::Idle;

		GetCharacterMovement()->MaxWalkSpeed = 500.f;
	}

	GetMesh()->GetAnimInstance()->StopAllMontages(0.f);

	Jump();

	StateType = EStateType::Jumping;
	StatusComponent->UseStamina(EActionType::Jump);

	Debug::Print(TEXT("Stamina"), StatusComponent->CurrentStamina, 3.f);
}

void ACPlayerCharacter::Dash()
{
	// 점프 중 대쉬 불가능, 대쉬 중 중복으로 대쉬 불가능
	if (StateType == EStateType::Jumping || StateType == EStateType::Dashing || StateType == EStateType::HeavyAttacking || StateType == EStateType::Switching || StateType == EStateType::ZoomIn)
	{
		return;
	}

	// 스태미너가 0이거나 소모치만큼 있지 않다면 사용 불가능
	if (!StatusComponent->CanDoAction(EActionType::Dash))
	{
		return;
	}

	if (StateType == EStateType::Guarding)
	{
		StateType = EStateType::Idle;

		GetCharacterMovement()->MaxWalkSpeed = 500.f;
	}

	GetMesh()->GetAnimInstance()->Montage_Play(DashMontage);

	StateType = EStateType::Dashing;
	StatusComponent->UseStamina(EActionType::Dash);

	Debug::Print(TEXT("Stamina"), StatusComponent->CurrentStamina, 3.f);
}

void ACPlayerCharacter::LeftClickStart()
{
	//LeftClickStartTime = FPlatformTime::Seconds();
}

void ACPlayerCharacter::LeftClickEnd()
{
	//LeftClickEndTime = FPlatformTime::Seconds();

	/*
	double ElapsedTime = LeftClickEndTime - LeftClickStartTime;
	if (ElapsedTime >= 1.f)
	{
		HeavyAttack();
	}
	else
	{
		LightAttack();
	}
	*/

	if (StateType == EStateType::HeavyAttackCharging)
	{
		HeavyAttack();
	}
	else
	{
		// 아무 무기도 장착하고 있지 않을 땐 공격 X
		if (WeaponComponent->CurrentWeaponMode == EWeaponModeType::None)
		{
			Debug::Print(TEXT("CurrentWeaponMode is None"), 2.f);
			return;
		}

		if (WeaponComponent->CurrentWeaponMode == EWeaponModeType::MeleeMode && WeaponComponent->MeleeWeapon == nullptr)
		{
			return;
		}

		if (WeaponComponent->CurrentWeaponMode == EWeaponModeType::RangeMode && WeaponComponent->RangeWeapon == nullptr)
		{
			return;
		}

		LightAttack();
	}

	//LeftClickStartTime = 0.f;
	//LeftClickEndTime = 0.f;
}

void ACPlayerCharacter::LeftClickTriggered()
{
	// 아무 무기도 장착하고 있지 않을 땐 공격 X
	if (WeaponComponent->CurrentWeaponMode == EWeaponModeType::None)
	{
		return;
	}

	// 점프, 대쉬, 막기 중에 차지 시작 불가능
	if (StateType == EStateType::Dashing || StateType == EStateType::Jumping || StateType == EStateType::Guarding || StateType == EStateType::Switching)
	{
		return;
	}

	// 스태미너가 0이거나 소모치만큼 있지 않다면 사용 불가능
	if (!StatusComponent->CanDoAction(EActionType::HeavyAttack))
	{
		return;
	}

	StateType = EStateType::HeavyAttackCharging;
}

void ACPlayerCharacter::RightClickStart()
{
	if (WeaponComponent->CurrentWeaponMode == EWeaponModeType::None)
	{
		return;
	}
	else if (WeaponComponent->CurrentWeaponMode == EWeaponModeType::MeleeMode && WeaponComponent->MeleeWeapon)
	{
		// 점프 중 가드 불가능, 대쉬 중 가드 불가능, 기본 공격 중 가드 불가능, 무기 스위칭 중에 가드 불가능
		if (StateType == EStateType::Jumping || StateType == EStateType::Dashing || StateType == EStateType::LightAttacking || StateType == EStateType::Switching)
		{
			return;
		}

		WeaponComponent->DoGuard();

		GetCharacterMovement()->MaxWalkSpeed = GuardWalkSpeed;

		// 스태미너 리젠 멈추기
		StatusComponent->StartBlocking();

		WeaponComponent->ResetCombo();

		StateType = EStateType::Guarding;
	}
	else if (WeaponComponent->CurrentWeaponMode == EWeaponModeType::RangeMode && WeaponComponent->RangeWeapon)
	{
		// 줌 인 불가능 상태들
		if (StateType == EStateType::Jumping || StateType == EStateType::Dashing || StateType == EStateType::Guarding || StateType == EStateType::Switching)
		{
			return;
		}

		// 원거리 무기를 장착하고 있을 땐 줌 인
		ZoomIn();

		StateType = EStateType::ZoomIn;
	}
}

void ACPlayerCharacter::RightClickEnd()
{
	if (StateType == EStateType::Guarding)
	{
		StatusComponent->EndBlocking();

		StateType = EStateType::Idle;

		GetCharacterMovement()->MaxWalkSpeed = 500.f;
	}

	if (WeaponComponent->CurrentWeaponMode == EWeaponModeType::RangeMode && WeaponComponent->RangeWeapon && StateType == EStateType::ZoomIn)
	{
		// 줌 아웃
		ZoomOut();

		StateType = EStateType::Idle;
	}
}

// TODO
// 아이템도 사용할 수 있는 조건을 지정해줘야 함
// ex) 점프 중엔 사용 불가, 대쉬 중엔 사용 불가 등등
void ACPlayerCharacter::Num1()
{

	InventoryComponent->UseQuickSlot(0);
}

void ACPlayerCharacter::Num2()
{
	InventoryComponent->UseQuickSlot(1);
}

void ACPlayerCharacter::Num3()
{
	InventoryComponent->UseQuickSlot(2);
}

void ACPlayerCharacter::Num4()
{
	InventoryComponent->UseQuickSlot(3);
}

void ACPlayerCharacter::Interaction()
{
	TArray<AActor*> OverlappingActors;
	InteractionBoundaryBoxComponent->GetOverlappingActors(OverlappingActors);

	FVector PlayerCharacterLocation = GetActorLocation();
	AActor* NearestActor = nullptr;
	float NearestDistance = 0.f;
	NearestActor = UGameplayStatics::FindNearestActor(PlayerCharacterLocation, OverlappingActors, NearestDistance);

	// 상호 작용 실행
	if (NearestActor != nullptr)
	{
		InteractionComponent->DoInteraction(NearestActor);
	}
}

void ACPlayerCharacter::OpenInventory()
{
	InventoryComponent->OpenInventoryWidget();
}

void ACPlayerCharacter::Tab()
{
	// 줌 상태에서 스위칭 하면 줌 상태 해제
	if (StateType == EStateType::ZoomIn)
	{
		ZoomOut();

		StateType = EStateType::Idle;
	}

	// Idle 상태일 때만 무기 스위칭 가능
	if (StateType != EStateType::Idle)
	{
		return;
	}

	StateType = EStateType::Switching;

	CurrentWeaponType = WeaponComponent->WeaponSwitching();

	// 근거리 무기를 들고 있고, 락 온 상태에서 원거리 무기로 스위칭하면 락 온 해제
	if (bIsLockOnNow)
	{
		if (WeaponComponent->CurrentWeaponMode == EWeaponModeType::RangeMode)
		{
			Debug::Print(TEXT("Disable Lock On"), 3.f);

			LockOnComponent->DisableLockOn();
		}
	}
}

void ACPlayerCharacter::WheelClick()
{
	// 원거리 무기를 들고 있을 땐 락온 불가
	if (WeaponComponent->CurrentWeaponMode == EWeaponModeType::RangeMode && WeaponComponent->RangeWeapon)
	{
		return;
	}

	LockOn();
}

void ACPlayerCharacter::WheelScroll(const FInputActionValue& Value)
{
	if (!bIsLockOnNow)
	{
		return;
	}

	float InputValue = Value.Get<float>();
	if (InputValue > 0.f)
	{
		LockOnComponent->SwitchTargetLockOn(1);
	}
	else if (InputValue < 0.f)
	{
		LockOnComponent->SwitchTargetLockOn(-1);
	}
}

void ACPlayerCharacter::LockOn()
{
	if (!bIsLockOnNow)
	{
		if (!LockOnComponent->DoLockOn())
		{
			return;
		}

		Debug::Print(TEXT("Lock On"), 3.f);

		GetCharacterMovement()->bOrientRotationToMovement = false;

		bIsLockOnNow = true;
	}
	else
	{
		Debug::Print(TEXT("Disable Lock On"), 3.f);

		LockOnComponent->DisableLockOn();
	}
}

void ACPlayerCharacter::LockOnOff()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bIsLockOnNow = false;
}

void ACPlayerCharacter::DisableLockOnTarget()
{
	LockOnComponent->DisableLockOn();
}

void ACPlayerCharacter::SetMovementRotationRate(FVector2D& InVector)
{
	FVector InputVector = FVector(InVector.X, InVector.Y, 0);

	FRotator InputVectorRotation = UKismetMathLibrary::MakeRotFromY(InputVector);
	FRotator FinalMovementRotation = UKismetMathLibrary::MakeRotator(0, 0, InputVectorRotation.Roll);

	FRotator ActorMovementRot = GetActorRotation();

	FRotator DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(FinalMovementRotation, ActorMovementRot);
	float FinalYaw = UKismetMathLibrary::Abs(DeltaRotation.Yaw);

	// 회전 각도에 따라 회전 속도 결정
	if (FinalYaw >= 0 && FinalYaw <= 45.f)
	{
		GetCharacterMovement()->RotationRate = FRotator(0, 500.f, 0);
	}
	else if (FinalYaw > 45.f && FinalYaw <= 90.f)
	{
		GetCharacterMovement()->RotationRate = FRotator(0, 650.f, 0);
	}
	else if (FinalYaw > 90.f && FinalYaw <= 135.f)
	{
		GetCharacterMovement()->RotationRate = FRotator(0, 750.f, 0);
	}
	else if (FinalYaw > 135.f && FinalYaw <= 180.f)
	{
		GetCharacterMovement()->RotationRate = FRotator(0, 900.f, 0);
	}
}

void ACPlayerCharacter::DashEnded()
{
	WeaponComponent->ResetCombo();

	StateType = EStateType::Idle;
}

void ACPlayerCharacter::DashInvincibleStart()
{
	bIsInvincible = true;

	Debug::Print(TEXT("Invincible start"), 3.f);
}

void ACPlayerCharacter::DashInvincibleEnd()
{
	bIsInvincible = false;

	Debug::Print(TEXT("Invincible end"), 3.f);
}

void ACPlayerCharacter::ResetComboAttack()
{
	WeaponComponent->ResetCombo();

	StateType = EStateType::Idle;
}

void ACPlayerCharacter::ComboStart()
{
	WeaponComponent->bCanNextCombo = false;
}

void ACPlayerCharacter::ComboWindowStart()
{
	WeaponComponent->bCanNextCombo = true;
}

void ACPlayerCharacter::ComboWindowEnd()
{
	WeaponComponent->bCanNextCombo = false;
}

void ACPlayerCharacter::HeavyAttackEnd()
{
	WeaponComponent->ResetCombo();

	StateType = EStateType::Idle;
}

void ACPlayerCharacter::RotationStartWhenAttack()
{
	GetCharacterMovement()->bAllowPhysicsRotationDuringAnimRootMotion = true;
}

void ACPlayerCharacter::RotationEndWhenAttack()
{
	GetCharacterMovement()->bAllowPhysicsRotationDuringAnimRootMotion = false;
}

void ACPlayerCharacter::JustGuardStart()
{
	bIsJustGuard = true;

	Debug::Print(TEXT("Just guard start"), 3.f);
}

void ACPlayerCharacter::JustGuardEnd()
{
	bIsJustGuard = false;

	Debug::Print(TEXT("Just guard end"), 3.f);
}

void ACPlayerCharacter::EquipWeapon1()
{
	WeaponComponent->EquipMeleeWeapon();
}

void ACPlayerCharacter::EquipWeapon2()
{
	WeaponComponent->EquipRangeWeapon();
}

void ACPlayerCharacter::WeaponSwitchingEnd()
{
	StateType = EStateType::Idle;
}

void ACPlayerCharacter::OnPlayerCharacterLanded(const FHitResult& Hit)
{
	StateType = EStateType::Idle;

	WeaponComponent->ResetCombo();
}

void ACPlayerCharacter::OnInteractionBoudaryBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ACPlayerCharacter::LightAttack()
{
	// 점프 중엔 기본 공격이 가능하나, 대쉬 중에는 기본 공격 불가능, 방어 중엔 기본 공격 불가능
	if (StateType == EStateType::Dashing || StateType == EStateType::Guarding || StateType == EStateType::HeavyAttacking || StateType == EStateType::Switching)
	{
		return;
	}

	// 스태미너가 0이거나 소모치만큼 있지 않다면 사용 불가능
	if (!StatusComponent->CanDoAction(EActionType::LightAttack))
	{
		return;
	}

	// 조건에 맞을 때만 공격 발동 (무의미한 스태미너 소모를 막기 위해)
	if (WeaponComponent->GetIsAttacking() && !WeaponComponent->bCanNextCombo)
	{
		return;
	}

	// TODO : 플레이어의 무기 상태에 따라 1번 무기의 콤보로 공격할지, 2번 무기의 콤보로 공격할지 정해야 함
	StateType = EStateType::LightAttacking;
	WeaponComponent->DoLightAttack();

	StatusComponent->UseStamina(EActionType::LightAttack);

	Debug::Print(TEXT("Stamina"), StatusComponent->CurrentStamina, 3.f);
}

void ACPlayerCharacter::HeavyAttack()
{
	// TODO : 플레이어의 무기 상태에 따라 1번 무기의 콤보로 공격할지, 2번 무기의 콤보로 공격할지 정해야 함
	StateType = EStateType::HeavyAttacking;
	WeaponComponent->DoHeavyAttack();

	StatusComponent->UseStamina(EActionType::HeavyAttack);

	Debug::Print(TEXT("Stamina"), StatusComponent->CurrentStamina, 3.f);
}

void ACPlayerCharacter::EquipWeapon(EWeaponType InWeaponType, TSoftClassPtr<AWeaponBase> InWeaponClass, uint8 InWeaponSlotType)
{
	if (InWeaponSlotType == 0)
	{
		WeaponTypes[0] = (uint8)InWeaponType;
		WeaponComponent->SpawnMeleeWeapon(InWeaponClass);
	}
	else if (InWeaponSlotType == 1)
	{
		WeaponTypes[1] = (uint8)InWeaponType;
		WeaponComponent->SpawnRangeWeapon(InWeaponClass);
	}
	else
	{
		return;
	}

	EquipWeaponRender();
}

void ACPlayerCharacter::UnEquipWeapon(uint8 InWeaponType)
{
	WeaponTypes[InWeaponType] = 0;

	WeaponComponent->UnEquipWeapon(InWeaponType);
}

bool ACPlayerCharacter::CanZoomIn()
{
	if (StateType == EStateType::Jumping || StateType == EStateType::Dashing || StateType == EStateType::Guarding || StateType == EStateType::Switching)
	{
		return false;
	}
	else
	{
		return true;
	}
}
