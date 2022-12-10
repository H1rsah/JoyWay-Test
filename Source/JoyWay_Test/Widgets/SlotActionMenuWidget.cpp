// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotActionMenuWidget.h"

#include "AmountWidget.h"
#include "InventoryWidget.h"
#include "JoyWayGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "JoyWay_Test/Components/InventoryComponent.h"

void USlotActionMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UseButton->OnClicked.AddDynamic(this, &ThisClass::UseItem);
	CancelButton->OnClicked.AddDynamic(this, &ThisClass::Close);
	SplitButton->OnClicked.AddDynamic(this, &ThisClass::SplitStack);
	ThrowButton->OnClicked.AddDynamic(this, &ThisClass::ThrowAway);
}

void USlotActionMenuWidget::Update(int32 InIndex, UInventoryComponent* InInventory, UInventoryWidget* InWidget)
{
	Index = InIndex;
	InventoryRef = InInventory;
	ParentWidgetRef = InWidget;

	bool IsEmpty;
	InventoryRef->GetSlotInfo(Index, IsEmpty, SlotInfo);
	const FInventoryItemInfo Item = GET_ITEM(SlotInfo.ItemId);

	if (Item.bCanBeUsed)
	{
		UseText->SetText(Item.UseText);
		UseButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UseButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	SplitButton->SetVisibility(Item.bCanBeStacked && SlotInfo.Amount > 1 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void USlotActionMenuWidget::UseItem()
{
	InventoryRef->UseItemAtIndex(Index);
	SetVisibility(ESlateVisibility::Hidden);
}

void USlotActionMenuWidget::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void USlotActionMenuWidget::SplitStack()
{
	InventoryRef->SplitStack(Index, SlotInfo.Amount / 2);
	SetVisibility(ESlateVisibility::Hidden);
}

void USlotActionMenuWidget::ThrowAway()
{
	if (IsValid(ParentWidgetRef))
	{
		ParentWidgetRef->AmountWidget->Update(Index, InventoryRef);
	}
	SetVisibility(ESlateVisibility::Hidden);
}
