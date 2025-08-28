// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Other/Struct.h"
#include "CPlayerCharacterStatusData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UCPlayerCharacterStatusData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Status")
	FPlayerStatus PlayerStatus;
};
