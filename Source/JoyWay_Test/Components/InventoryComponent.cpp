// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "JoyWayGameInstance.h"
#include "PickupActor.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::GetSlotInfo(int32 Index, bool& IsEmpty, FInventorySlot& SlotInfo)
{
	if (Items[Index].Amount > -1)
	{
		IsEmpty = false;
		SlotInfo = Items[Index];
	}
	else
	{
		IsEmpty = true;
	}
}

void UInventoryComponent::AddItem(FInventorySlot SlotInfo, bool ShowNotification)
{
	const FInventoryItemInfo Item = GET_ITEM(SlotInfo.ItemId);
	if (Item.bCanBeStacked)
	{
		int32 FoundIndex = SearchFreeStack(SlotInfo.ItemId); // Search slot with Item
		if (FoundIndex >= 0)
		{
			// Add amount to slot and return values
			Items[FoundIndex].Amount += SlotInfo.Amount;
		}
		else
		{
			// Search for empty slot
			if (SearchEmptySlot() == -1)
			{
				Items.Add(SlotInfo);
			}
		}
	}
	else
	{
		for (int32 i=0; i<SlotInfo.Amount; i++)
		{
			// Search for empty slot
			if (SearchEmptySlot() == -1)
			{
				Items.Add(FInventorySlot(SlotInfo.ItemId, 1));
			}
		}
	}

	if (ShowNotification)
	{
		ObtainedItemsQueue.Add(SlotInfo);
		OnObtainItem.Broadcast();
	}
					
	OnInventoryUpdated.Broadcast();
}

void UInventoryComponent::AddItemAtIndex(int32 Index, FInventorySlot SlotInfo, bool ShowNotification)
{
	if (Items[Index].Amount > 0)
	{
		Items[Index].Amount += SlotInfo.Amount;

		if (ShowNotification)
		{
			ObtainedItemsQueue.Add(SlotInfo);
			OnObtainItem.Broadcast();
		}

		OnInventoryUpdated.Broadcast();
	}
}

FInventoryItemInfo UInventoryComponent::GetItemInfo(const FName ItemId) const
{
	return GET_ITEM(ItemId);
}

void UInventoryComponent::ThrowAway(int32 Index, int64 Amount)
{
	if (Amount > 0)
	{
		const FActorSpawnParameters SpawnInfo;
		const FVector Location = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 100;
		
		const FInventoryItemInfo Item = GET_ITEM(Items[Index].ItemId);
		APickupActor* ActorToSpawn = GetWorld()->SpawnActor<APickupActor>(Location, GetOwner()->GetActorRotation(), SpawnInfo);
		ActorToSpawn->SetNewItem(Item, Amount);
		
		RemoveItemAtIndex(Index, Amount, false);
	}
}

void UInventoryComponent::UseItemAtIndex(int32 Index)
{
	if (Items[Index].Amount > -1)
	{
		RemoveItemAtIndex(Index, 1, true);
		GEngine->AddOnScreenDebugMessage(-1,1,FColor::Orange,"Item is Used:");
		// GetWorld()->SpawnActor<AMasterItem>(FActorSpawnParameters())->Use();
	}	
}

bool UInventoryComponent::SplitStack(int32 Index, int32 Amount)
{
	if (IsSlotEmpty(Index))
		return false;
	
	if (Items[Index].Amount > Amount)
		{
		int32 Id = SearchEmptySlot();
		Items[Index].Amount -= Amount;
		if (Id >= 0)
		{
			Items[Id].Amount = Amount;
			Items[Id].ItemId = Items[Index].ItemId;
		}
		else
		{
			Items.Add(FInventorySlot(Items[Index].ItemId, Amount));
		}
		
		// Update UI
		OnInventoryUpdated.Broadcast();
		return true;
		}
	return false;
}

bool UInventoryComponent::RemoveItemAtIndex(int32 Index, int32 Amount, bool ShowNotification)
{
	if (Amount > 0 && !IsSlotEmpty(Index))
	{

		if (ShowNotification)
		{
			OnObtainItem.Broadcast();
		}
		
		if (Amount >= GetAmountAtIndex(Index))
		{
			Items.RemoveAt(Index);
		}
		else
		{
			Items[Index].Amount -= Amount;
		}
		
		// Update UI
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}
void UInventoryComponent::RemoveItemAmount(FName ItemId, int32 Amount, bool ShowNotification, int32 &RemovedAmount)
{
	int32 ItemsLeft = Amount;
	int32 FoundIndex;
	
	do
	{
		FoundIndex = SearchFreeStack(ItemId);
		if (FoundIndex >= 0)
		{
			const int32 RemoveAmount = Items[FoundIndex].Amount >= ItemsLeft ? ItemsLeft : Items[FoundIndex].Amount;
			RemoveItemAtIndex(FoundIndex, RemoveAmount, false);
			ItemsLeft -= RemoveAmount;
		}
	}
	while (ItemsLeft > 0 && FoundIndex > -1);

	RemovedAmount =  Amount - ItemsLeft;
}

void UInventoryComponent::SwapSlots(int32 Slot1, int32 Slot2)
{
	FInventorySlot Tmp = Items[Slot1];

	Items[Slot1] = Items[Slot2];
	Items[Slot2] = Tmp;
	
	// Update UI
	OnInventoryUpdated.Broadcast();
}


bool UInventoryComponent::IsSlotEmpty(int32 Index)
{
	if (Items[Index].Amount > 0)
	{
		return false;
	}
	return true;
}

int32 UInventoryComponent::SearchEmptySlot()
{
	int32 Index = -1;
	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (Items[i].Amount <= 0)
		{
			Index = i;
			break;
		}
	}
	return Index;
}

int32 UInventoryComponent::SearchFreeStack(FName ItemId)
{
	int32 Index = -1;
	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (ItemId == Items[i].ItemId )
		{
			Index = i;
			break;
		}
	}
	return Index;
}


