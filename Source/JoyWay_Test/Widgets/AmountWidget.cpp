// Fill out your copyright notice in the Description page of Project Settings.


#include "AmountWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "JoyWay_Test/Components/InventoryComponent.h"
#include "JoyWay_Test/GameData/GameData.h"

void UAmountWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OKButton->OnClicked.AddDynamic(this, &ThisClass::Close);

	AmountSlider->SetStepSize(1);
}

void UAmountWidget::Update(int32 InIndex, UInventoryComponent* InInventory)
{
	Index = InIndex;
	InventoryRef = InInventory;

	FInventorySlot SlotInfo;
	bool IsEmpty;
	InventoryRef->GetSlotInfo(Index, IsEmpty, SlotInfo);
	MaxValueText->SetText(FText::AsNumber(SlotInfo.Amount));
	AmountSlider->SetValue(0);
	AmountSlider->SetMaxValue(SlotInfo.Amount);

	SetVisibility(ESlateVisibility::Visible);
}

void UAmountWidget::Close()
{
	InventoryRef->ThrowAway(Index, AmountSlider->GetValue());
	SetVisibility(ESlateVisibility::Hidden);
}
