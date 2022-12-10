// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JoyWay_Test/GameData/GameData.h"
#include "InventoryComponent.generated.h"

// UI update delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObtainItem);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOYWAY_TEST_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	UFUNCTION(BlueprintPure)
	void GetSlotInfo(int32 Index, bool& IsEmpty, FInventorySlot& SlotInfo);
	UFUNCTION(BlueprintCallable)
	void AddItem(FInventorySlot SlotInfo, bool ShowNotification);
	UFUNCTION(BlueprintCallable)
	bool RemoveItemAtIndex(int32 Index, int32 Amount, bool ShowNotification);
	void RemoveItemAmount(FName ItemId, int32 Amount, bool ShowNotification, int32 &RemovedAmount);

	
	void SwapSlots(int32 Slot1, int32 Slot2);
	void AddItemAtIndex(int32 Index, FInventorySlot SlotInfo, bool ShowNotification);
	FInventoryItemInfo GetItemInfo(const FName ItemId) const;

	UFUNCTION(BlueprintCallable)
	void ThrowAway(int32 Index, int64 Amount);
	UFUNCTION(BlueprintCallable)
	void UseItemAtIndex(int32 Index);
	UFUNCTION(BlueprintCallable)
	bool SplitStack(int32 Index, int32 Amount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventorySlot> Items;
	UPROPERTY()
	TArray<FInventorySlot> ObtainedItemsQueue;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnObtainItem OnObtainItem;

	UPROPERTY(EditAnywhere, Category = "Storage")
	TSubclassOf<UUserWidget> WidgetClass;

protected:
	bool IsSlotEmpty(int32 Index);
	int32 SearchEmptySlot();

private:
	int32 SearchFreeStack(FName ItemId);
	int32 GetAmountAtIndex(int32 Index) { return Items[Index].Amount; };
};
