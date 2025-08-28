// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CEnemyCharacter.generated.h"

class AAIController;

UCLASS()
class PROJECTCHRONOS_API ACEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACEnemyCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<AAIController> EnemyController;
};
