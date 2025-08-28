// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestItemActionMenu.generated.h"

class UInventoryComponent;

/**
 * 
 */
UCLASS()
class PROJECTCHRONOS_API UQuestItemActionMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UQuestItemActionMenu(const FObjectInitializer& ObjectInitializer);


#pragma region Variable
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action Menu Widget|Variable", meta = (AllowPrivateAccess = "true"))
	int32 QuestItemSlotIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Action Menu Widget|Variable")
	TWeakObjectPtr<UInventoryComponent> InventoryComponent;
#pragma endregion


#pragma region Function
public:
	UFUNCTION(BlueprintCallable)
	void SetData(const int32& InQuestItemSlotIndex);
#pragma endregion
};
