// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "InventorySlotWidget.h"
#include "JoyWayGameInstance.h"
#include "SlotActionMenuWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "JoyWay_Test/Components/InventoryComponent.h"
#include "JoyWay_Test/GameData/GameData.h"

void UInventoryWidget::NativeConstruct()
{
	InventoryRef = GetOwningPlayerPawn()->FindComponentByClass<UInventoryComponent>();
	
	if (InventoryRef)
	{
		InventoryRef->OnInventoryUpdated.AddDynamic(this, &ThisClass::InitializeInventory);
		
		Super::NativeConstruct();

		InitializeInventory();
	}
}

void UInventoryWidget::InitializeInventory()
{
	if (!SlotWidgetClass)
	{
		return;
	}

	SlotBox->ClearChildren();
	float InventoryWeight = 0.f;

	for (int32 i = 0; i < InventoryRef->Items.Num(); i++)
	{
		const FInventoryItemInfo Item = GET_ITEM(InventoryRef->Items[i].ItemId);
		InventoryWeight += Item.Weight * InventoryRef->Items[i].Amount;

		if (Item.Type == DisplayByType || !IsSortingRequired)
		{
			UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
			SlotBox->AddChildToWrapBox(NewSlot);
			
			NewSlot->SetValues(Item, InventoryRef->Items[i], InventoryRef, this, i);
			NewSlot->OnItemDrop.AddUObject(this, &ThisClass::OnItemDropFunc);
		}
	}

	FNumberFormattingOptions Options;
	Options.MinimumFractionalDigits = 2;
	Options.MaximumFractionalDigits = 2;
	WeightText->SetText(FText::AsNumber(InventoryWeight, &Options));
}

void UInventoryWidget::OnRightClick(int32 Index)
{
	ActionMenuWidget->SetRenderTranslation(UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()));
	ActionMenuWidget->Update(Index, InventoryRef, this);
	ActionMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryWidget::OnItemDropFunc(UInventorySlotWidget* From, UInventorySlotWidget* To)
{
	if (To->SlotInfo.ItemId == From->SlotInfo.ItemId)
	{
		To->InventoryRef->AddItemAtIndex(To->SlotID, From->SlotInfo, false);
		From->InventoryRef->RemoveItemAtIndex(From->SlotID, From->SlotInfo.Amount, false);
	}
	else
	{
		To->InventoryRef->SwapSlots(From->SlotID, To->SlotID);
	}
}
