// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotToolTipWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USlotToolTipWidget::SetValues(FInventoryItemInfo InItem, int32 InAmount)
{
	ItemInfo = InItem;
	Amount = InAmount;

	ItemIcon->SetBrushFromTexture(ItemInfo.Icon.LoadSynchronous());
	NameText->SetText(ItemInfo.Name);
	DescriptionText->SetText(ItemInfo.Description);
	TypeText->SetText(UEnum::GetDisplayValueAsText(ItemInfo.Type));
	
	FNumberFormattingOptions Options;
	Options.UseGrouping = false;
	Options.MaximumFractionalDigits = 2;
	Options.MinimumFractionalDigits = 0;
	SummaryWeightText->SetText(FText::AsNumber(ItemInfo.Weight * Amount, &Options));
	Options.MaximumFractionalDigits = 3;
	WeightText->SetText(FText::FromString(FString::Printf(TEXT("(%s)"), *FText::AsNumber(ItemInfo.Weight, &Options).ToString())));
}
