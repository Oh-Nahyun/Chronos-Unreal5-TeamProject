// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/StatusComponent.h"

#include "Data/DataAsset/CPlayerCharacterStatusData.h"

#include "Other/Debug.h"

UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	MaxHealth = 0.f;
	MaxStamina = 0.f;
	JumpStaminaUse = 0.f;
	DashStaminaUse = 0.f;
	LightAttackStaminaUse = 0.f;
	HeavyAttackStaminaUse = 0.f;
	GuardSuccessStaminaUse = 0.f;
	StaminaRegenAmount = 0.f;
	StaminaRegenPeriod = 1.f;

	CurrentHealth = 0.f;
	CurrentStamina = 0.f;
	Attack = 0.f;
	Defense = 0.f;
	CriticalChance = 0.f;
	CriticalDamageCoefficient = 0.f;
}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// Start Stamina Regen
	bool bLoopTimer = true;
	GetWorld()->GetTimerManager().SetTimer(StaminaRegenTimerHandle, this, &UStatusComponent::RegenStamina, StaminaRegenPeriod, bLoopTimer);
}

void UStatusComponent::InitStatusData()
{
	MaxHealth = StatusDataAsset->PlayerStatus.MaxHealth;
	MaxStamina = StatusDataAsset->PlayerStatus.MaxStamina;
	JumpStaminaUse = StatusDataAsset->PlayerStatus.JumpStaminaUse;
	DashStaminaUse = StatusDataAsset->PlayerStatus.DashStaminaUse;
	LightAttackStaminaUse = StatusDataAsset->PlayerStatus.LightAttackStaminaUse;
	HeavyAttackStaminaUse = StatusDataAsset->PlayerStatus.HeavyAttackStaminaUse;
	GuardSuccessStaminaUse = StatusDataAsset->PlayerStatus.GuardSuccessStaminaUse;
	StaminaRegenAmount = StatusDataAsset->PlayerStatus.StaminaRegenAmount;

	CurrentHealth = MaxHealth;
	CurrentStamina = MaxStamina;
	Attack = 0.f;
	Defense = 0.f;
	CriticalChance = .1f;
	CriticalDamageCoefficient = 1.f;
}

void UStatusComponent::UseStamina(EActionType InActionType)
{
	switch (InActionType)
	{
	case EActionType::Jump:
	{
		CurrentStamina = FMath::Clamp(CurrentStamina - JumpStaminaUse, 0.f, CurrentStamina);
		StopRegen();
		GetWorld()->GetTimerManager().SetTimer(RegenStopTimerHandle, this, &UStatusComponent::StartRegen, 2.f, false);
		break;
	}
	case EActionType::Dash:
	{
		CurrentStamina -= DashStaminaUse;
		StopRegen();
		GetWorld()->GetTimerManager().SetTimer(RegenStopTimerHandle, this, &UStatusComponent::StartRegen, 2.f, false);
		break;
	}
	case EActionType::LightAttack:
	{
		CurrentStamina -= LightAttackStaminaUse;
		StopRegen();
		GetWorld()->GetTimerManager().SetTimer(RegenStopTimerHandle, this, &UStatusComponent::StartRegen, 2.f, false);
		break;
	}
	case EActionType::HeavyAttack:
	{
		CurrentStamina -= HeavyAttackStaminaUse;
		StopRegen();
		GetWorld()->GetTimerManager().SetTimer(RegenStopTimerHandle, this, &UStatusComponent::StartRegen, 2.f, false);
		break;
	}
	default:
		break;
	}
}

bool UStatusComponent::CanDoAction(EActionType InActionType)
{
	switch (InActionType)
	{
	case EActionType::Jump:
	{
		if (CurrentStamina < JumpStaminaUse || CurrentStamina <= 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	case EActionType::Dash:
	{
		if (CurrentStamina < DashStaminaUse || CurrentStamina <= 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	case EActionType::LightAttack:
	{
		if (CurrentStamina < LightAttackStaminaUse || CurrentStamina <= 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	case EActionType::HeavyAttack:
	{
		if (CurrentStamina < HeavyAttackStaminaUse || CurrentStamina <= 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	default:
		return true;
	}
}

void UStatusComponent::StartBlocking()
{
	StopRegen();
}

void UStatusComponent::EndBlocking()
{
	StartRegen();
}

void UStatusComponent::GuardSuccess()
{
	CurrentStamina = FMath::Clamp(CurrentStamina - GuardSuccessStaminaUse, 0.f, CurrentStamina);

	if (CurrentStamina <= 0)
	{
		// TODO
		// 막다가 스태미너가 0이 된 경우 탈진에 빠짐
	}
}

void UStatusComponent::RegenStamina()
{
	if (CurrentStamina >= MaxStamina)
	{
		StopRegen();
		return;
	}

	CurrentStamina = FMath::Clamp(CurrentStamina + StaminaRegenAmount, 0.f, MaxStamina);

	Debug::Print(TEXT("Stamina"), CurrentStamina, 2.f);
}

void UStatusComponent::StopRegen()
{
	GetWorld()->GetTimerManager().PauseTimer(StaminaRegenTimerHandle);
}

void UStatusComponent::StartRegen()
{
	RegenStopTimerHandle.Invalidate();

	GetWorld()->GetTimerManager().UnPauseTimer(StaminaRegenTimerHandle);
}

float UStatusComponent::TakeDamage(float InDamage)
{
	// TODO
	// 데미지 계산식에 따라 방어력과 치명타 등등을 고려해서 체력 감소
	return 0.0f;
}

//void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//}
