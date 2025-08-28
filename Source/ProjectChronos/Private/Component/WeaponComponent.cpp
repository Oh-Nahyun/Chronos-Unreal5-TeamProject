// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/WeaponComponent.h"

//#include "GameFramework/Character.h"
#include "Character/CPlayerCharacter.h"
//#include "Engine/AssetManager.h"
//#include "Engine/StreamableManager.h"

#include "Object/Weapon/WeaponBase.h"

#include "Other/Debug.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	MeleeWeaponClass = nullptr;
	MeleeWeapon = nullptr;
	RangeWeaponClass = nullptr;
	RangeWeapon = nullptr;

	MeleeWeaponHeavyAttackAnim = nullptr;
	MeleeWeaponGuardAnim = nullptr;
	RangeWeaponHeavyAttackAnim = nullptr;

	CurrentComboCount = 0;
	MaxComboCount = 0;

	bIsAttacking = false;
	bCanNextCombo = false;

	OwningPlayerCharacter = nullptr;

	CurrentWeaponState = 0;
	CurrentWeaponMode = EWeaponModeType::None;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	MeleeWeaponComboAnims.Empty();
	RangeWeaponComboAnims.Empty();
}

void UWeaponComponent::InitializeOwner()
{
	if (OwningPlayerCharacter == nullptr)
	{
		OwningPlayerCharacter = CastChecked<ACPlayerCharacter>(GetOwner());
	}
}

void UWeaponComponent::SpawnMeleeWeapon(TSoftClassPtr<AWeaponBase> InWeaponClass)
{
	if (InWeaponClass.IsPending())
	{
		MeleeWeaponClass = InWeaponClass.LoadSynchronous();

		MeleeWeapon = GetWorld()->SpawnActor<AWeaponBase>(MeleeWeaponClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
		MeleeWeapon->OwnerPlayerCharacter = GetOwner<ACharacter>();
		MeleeWeapon->SetOwner(GetOwner());

		//FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
		for (TSoftObjectPtr<UAnimMontage> AnimMontage : MeleeWeapon->ComboMontages)
		{
			TObjectPtr<UAnimMontage> LoadedMontage = AnimMontage.LoadSynchronous();
			MeleeWeaponComboAnims.AddUnique(LoadedMontage);

			//TObjectPtr<UAnimMontage> LoadedMontage = StreamableManager.LoadSynchronous(AnimMontage);
			//MeleeWeaponComboAnims.AddUnique(LoadedMontage);

			//TSharedPtr<FStreamableHandle> Handle = StreamableManager.RequestSyncLoad(AnimMontage.ToSoftObjectPath());
			//Handle->ReleaseHandle();
		}

		MeleeWeaponHeavyAttackAnim = MeleeWeapon->HeavyAttackMontage.LoadSynchronous();
		MeleeWeaponGuardAnim = MeleeWeapon->GuardMontage.LoadSynchronous();
		MeleeWeaponEquipAnim = MeleeWeapon->EquipMontage.LoadSynchronous();

		if (CurrentWeaponMode == EWeaponModeType::None || CurrentWeaponMode == EWeaponModeType::RangeMode)
		{
			MeleeWeapon->AttachOnPlayerCharacter();
		}
		else if (CurrentWeaponMode == EWeaponModeType::MeleeMode)
		{
			MeleeWeapon->EquipOnPlayerCharacter();
			OwningPlayerCharacter->CurrentWeaponType = MeleeWeapon->WeaponType;
		}

		MaxComboCount = MeleeWeapon->ComboMontages.Num();
	}
	else
	{
		MeleeWeaponClass = InWeaponClass.Get();

		MeleeWeapon = GetWorld()->SpawnActor<AWeaponBase>(MeleeWeaponClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
		MeleeWeapon->OwnerPlayerCharacter = GetOwner<ACharacter>();
		MeleeWeapon->SetOwner(GetOwner());

		for (TSoftObjectPtr<UAnimMontage> AnimMontage : MeleeWeapon->ComboMontages)
		{
			TObjectPtr<UAnimMontage> LoadedMontage = AnimMontage.LoadSynchronous();
			MeleeWeaponComboAnims.AddUnique(LoadedMontage);
		}

		MeleeWeaponHeavyAttackAnim = MeleeWeapon->HeavyAttackMontage.LoadSynchronous();
		MeleeWeaponGuardAnim = MeleeWeapon->GuardMontage.LoadSynchronous();
		MeleeWeaponEquipAnim = MeleeWeapon->EquipMontage.LoadSynchronous();

		if (CurrentWeaponMode == EWeaponModeType::None || CurrentWeaponMode == EWeaponModeType::RangeMode)
		{
			MeleeWeapon->AttachOnPlayerCharacter();
		}
		else if (CurrentWeaponMode == EWeaponModeType::MeleeMode)
		{
			MeleeWeapon->EquipOnPlayerCharacter();
			OwningPlayerCharacter->CurrentWeaponType = MeleeWeapon->WeaponType;
		}

		MaxComboCount = MeleeWeapon->ComboMontages.Num();
	}
}

void UWeaponComponent::SpawnRangeWeapon(TSoftClassPtr<AWeaponBase> InWeaponClass)
{
	if (InWeaponClass.IsPending())
	{
		RangeWeaponClass = InWeaponClass.LoadSynchronous();

		RangeWeapon = GetWorld()->SpawnActor<AWeaponBase>(RangeWeaponClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
		RangeWeapon->OwnerPlayerCharacter = GetOwner<ACharacter>();
		RangeWeapon->SetOwner(GetOwner());

		RangeWeaponHeavyAttackAnim = RangeWeapon->HeavyAttackMontage.LoadSynchronous();
		RangeWeaponEquipAnim = RangeWeapon->EquipMontage.LoadSynchronous();

		if (CurrentWeaponMode == EWeaponModeType::None || CurrentWeaponMode == EWeaponModeType::MeleeMode)
		{
			RangeWeapon->AttachOnPlayerCharacter();
		}
		else if (CurrentWeaponMode == EWeaponModeType::RangeMode)
		{
			RangeWeapon->EquipOnPlayerCharacter();
			OwningPlayerCharacter->CurrentWeaponType = RangeWeapon->WeaponType;

			// 원거리 무기 착용하면 락 온 해제
			if (OwningPlayerCharacter->bIsLockOnNow)
			{
				Debug::Print(TEXT("Disable Lock On"), 3.f);

				OwningPlayerCharacter->DisableLockOnTarget();
			}
		}
	}
	else
	{
		RangeWeaponClass = InWeaponClass.Get();

		RangeWeapon = GetWorld()->SpawnActor<AWeaponBase>(RangeWeaponClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
		RangeWeapon->OwnerPlayerCharacter = GetOwner<ACharacter>();
		RangeWeapon->SetOwner(GetOwner());

		RangeWeaponHeavyAttackAnim = RangeWeapon->HeavyAttackMontage.LoadSynchronous();
		RangeWeaponEquipAnim = RangeWeapon->EquipMontage.LoadSynchronous();

		if (CurrentWeaponMode == EWeaponModeType::None || CurrentWeaponMode == EWeaponModeType::MeleeMode)
		{
			RangeWeapon->AttachOnPlayerCharacter();
		}
		else if (CurrentWeaponMode == EWeaponModeType::RangeMode)
		{
			RangeWeapon->EquipOnPlayerCharacter();
			OwningPlayerCharacter->CurrentWeaponType = RangeWeapon->WeaponType;

			// 원거리 무기 착용하면 락 온 해제
			if (OwningPlayerCharacter->bIsLockOnNow)
			{
				Debug::Print(TEXT("Disable Lock On"), 3.f);

				OwningPlayerCharacter->DisableLockOnTarget();
			}
		}
	}
}

void UWeaponComponent::UnEquipWeapon(uint8 InWeaponType)
{
	if (InWeaponType == 0)
	{
		CurrentComboCount = 0;
		MaxComboCount = 0;

		MeleeWeaponComboAnims.Empty();
		MeleeWeaponHeavyAttackAnim = nullptr;
		MeleeWeaponGuardAnim = nullptr;
		MeleeWeaponEquipAnim = nullptr;

		//CurrentMeleeWeapon->UnLoadComboMontages();

		//FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
		//for (TSoftObjectPtr<UAnimMontage> AnimMontage : CurrentMeleeWeapon->ComboMontages)
		//{
		//	StreamableManager.Unload(AnimMontage.ToSoftObjectPath());
		//}

		MeleeWeapon->DetachOnPlayerCharacter();
		MeleeWeapon->Destroy();
		MeleeWeapon = nullptr;
		MeleeWeaponClass = nullptr;
	}
	else if (InWeaponType == 1)
	{
		RangeWeaponComboAnims.Empty();
		RangeWeaponHeavyAttackAnim = nullptr;
		RangeWeaponEquipAnim = nullptr;

		RangeWeapon->DetachOnPlayerCharacter();
		RangeWeapon->Destroy();
		RangeWeapon = nullptr;
		RangeWeaponClass = nullptr;
	}

	/*
	// 장비를 해제했을 때 어떤 장비도 착용하고 있는 상태가 아니라면 초기화
	if (MeleeWeapon == nullptr && RangeWeapon == nullptr)
	{
		CurrentWeaponState = 0;
		OwningPlayerCharacter->CurrentWeaponType = EWeaponType::None;
	}
	*/

	// 만약 1번 무기를 착용하고 있었는데 1번 무기를 해제한 거라면 초기화
	// 2번 무기를 들고 있는 상태에서 1번 무기를 해제했다면 그대로 2번 무기 폼으로 유지
	if (CurrentWeaponMode == EWeaponModeType::MeleeMode && MeleeWeapon == nullptr)
	{
		OwningPlayerCharacter->CurrentWeaponType = EWeaponType::None;
	}

	// 만약 2번 무기를 착용하고 있었는데 2번 무기를 해제한 거라면 초기화
	// 1번 무기를 들고 있는 상태에서 2번 무기를 해제했다면 그대로 1번 무기 폼으로 유지
	if (CurrentWeaponMode == EWeaponModeType::RangeMode && RangeWeapon == nullptr)
	{
		OwningPlayerCharacter->CurrentWeaponType = EWeaponType::None;
	}
}

void UWeaponComponent::DoLightAttack()
{
	if (CurrentWeaponMode == EWeaponModeType::MeleeMode && MeleeWeapon->WeaponEquipState == EWeaponEquipStateType::Equipped)
	{
		if (bIsAttacking)
		{
			if (bCanNextCombo)
			{
				SetComboCount();
			}
			else
			{
				return;
			}
		}
		else
		{
			SetComboCount();
		}
	}
	else if (CurrentWeaponMode == EWeaponModeType::RangeMode && RangeWeapon->WeaponEquipState == EWeaponEquipStateType::Equipped)
	{
		// 원거리 기본 공격 구현
		OwningPlayerCharacter->StateType = EStateType::Idle;
	}
}

void UWeaponComponent::DoHeavyAttack()
{
	if (CurrentWeaponMode == EWeaponModeType::MeleeMode && MeleeWeapon->WeaponEquipState == EWeaponEquipStateType::Equipped)
	{
		if (MeleeWeaponHeavyAttackAnim)
		{
			OwningPlayerCharacter->GetMesh()->GetAnimInstance()->Montage_Play(MeleeWeaponHeavyAttackAnim);
		}
	}
	else if (CurrentWeaponMode == EWeaponModeType::RangeMode && RangeWeapon->WeaponEquipState == EWeaponEquipStateType::Equipped)
	{
		if (RangeWeaponHeavyAttackAnim)
		{
			OwningPlayerCharacter->GetMesh()->GetAnimInstance()->Montage_Play(RangeWeaponHeavyAttackAnim);
		}
	}
}

void UWeaponComponent::SetComboCount()
{
	if (UAnimMontage* LightAttackMontage = MeleeWeaponComboAnims[CurrentComboCount])
	{
		OwningPlayerCharacter->GetMesh()->GetAnimInstance()->Montage_Play(LightAttackMontage);
	}

	CurrentComboCount += 1;

	if (CurrentComboCount > MaxComboCount)
	{
		CurrentComboCount = 0;
	}

	bIsAttacking = true;
}

void UWeaponComponent::ResetCombo()
{
	bIsAttacking = false;
	CurrentComboCount = 0;
	bCanNextCombo = false;
}

void UWeaponComponent::DoGuard()
{
	if (MeleeWeaponGuardAnim)
	{
		OwningPlayerCharacter->GetMesh()->GetAnimInstance()->Montage_Play(MeleeWeaponGuardAnim);
	}
}

const EWeaponType UWeaponComponent::WeaponSwitching()
{
	if (CurrentWeaponMode == EWeaponModeType::None)
	{
		if (MeleeWeapon == nullptr && RangeWeapon == nullptr)
		{
			OwningPlayerCharacter->StateType = EStateType::Idle;
			return EWeaponType::None;
		}
		else if (MeleeWeapon != nullptr && RangeWeapon == nullptr)
		{
			CurrentWeaponMode = EWeaponModeType::MeleeMode;

			OwningPlayerCharacter->GetMesh()->GetAnimInstance()->Montage_Play(MeleeWeaponEquipAnim);

			return MeleeWeapon->WeaponType;
		}
		else if (MeleeWeapon == nullptr && RangeWeapon != nullptr)
		{
			CurrentWeaponMode = EWeaponModeType::RangeMode;

			OwningPlayerCharacter->GetMesh()->GetAnimInstance()->Montage_Play(RangeWeaponEquipAnim);

			return RangeWeapon->WeaponType;
		}
		else
		{
			CurrentWeaponMode = EWeaponModeType::MeleeMode;

			OwningPlayerCharacter->GetMesh()->GetAnimInstance()->Montage_Play(MeleeWeaponEquipAnim);

			return MeleeWeapon->WeaponType;
		}
	}
	else if (CurrentWeaponMode == EWeaponModeType::MeleeMode)
	{
		// 둘 다 장착 중이 아닌 경우
		if (MeleeWeapon == nullptr && RangeWeapon == nullptr)
		{
			OwningPlayerCharacter->StateType = EStateType::Idle;
			return EWeaponType::None;
		}

		// 하나만 장착하고 있을 때
		if (RangeWeapon == nullptr)
		{
			OwningPlayerCharacter->StateType = EStateType::Idle;
			return MeleeWeapon->WeaponType;
		}
		else
		{
			CurrentWeaponMode = EWeaponModeType::RangeMode;

			if (MeleeWeapon)
			{
				MeleeWeapon->AttachOnPlayerCharacter();
			}

			OwningPlayerCharacter->GetMesh()->GetAnimInstance()->Montage_Play(RangeWeaponEquipAnim);

			return RangeWeapon->WeaponType;
		}
	}
	else if (CurrentWeaponMode == EWeaponModeType::RangeMode)
	{
		// 둘 다 장착 중이 아닌 경우
		if (MeleeWeapon == nullptr && RangeWeapon == nullptr)
		{
			OwningPlayerCharacter->StateType = EStateType::Idle;
			return EWeaponType::None;
		}

		// 하나만 장착하고 있을 때
		if (MeleeWeapon == nullptr)
		{
			OwningPlayerCharacter->StateType = EStateType::Idle;
			return RangeWeapon->WeaponType;
		}
		else
		{
			CurrentWeaponMode = EWeaponModeType::MeleeMode;

			if (RangeWeapon)
			{
				RangeWeapon->AttachOnPlayerCharacter();
			}

			OwningPlayerCharacter->GetMesh()->GetAnimInstance()->Montage_Play(MeleeWeaponEquipAnim);

			return MeleeWeapon->WeaponType;
		}
	}
	else
	{
		OwningPlayerCharacter->StateType = EStateType::Idle;
		return EWeaponType::None;
	}
}

void UWeaponComponent::EquipMeleeWeapon()
{
	if (MeleeWeapon)
	{
		MeleeWeapon->EquipOnPlayerCharacter();
	}
}

void UWeaponComponent::EquipRangeWeapon()
{
	if (RangeWeapon)
	{
		RangeWeapon->EquipOnPlayerCharacter();
	}
}
