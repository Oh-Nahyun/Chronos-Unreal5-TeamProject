// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MaterialActionMenu.generated.h"

class UInventoryComponent;

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UMaterialActionMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMaterialActionMenu(const FObjectInitializer& ObjectInitializer);


#pragma region Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action Menu Widget|Variable", meta = (AllowPrivateAccess = "true"))
	int32 MaterialSlotIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action Menu Widget|Variable")
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;
#pragma endregion


#pragma region Function
public:
	UFUNCTION(BlueprintCallable)
	void SetData(const int32& InMaterialSlotIndex);
#pragma endregion
};
