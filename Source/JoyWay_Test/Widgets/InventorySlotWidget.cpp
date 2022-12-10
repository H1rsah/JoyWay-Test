// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlotWidget.h"
#include "InventoryWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DragDropOperations/SlotDragDropOperation.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UInventorySlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		ParentWidgetRef->OnRightClick(SlotID);
	}
	else
	{
		if (bIsDraggable && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
		}
	}
	return FReply::Handled();
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(USlotDragDropOperation::StaticClass());
	if (USlotDragDropOperation* SlotOperation = Cast<USlotDragDropOperation>(OutOperation))
	{
		SlotOperation->DefaultDragVisual=this;

		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
}

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	USlotDragDropOperation* SlotOperation = Cast<USlotDragDropOperation>(InOperation);
	if (SlotOperation && SlotOperation->DefaultDragVisual && SlotOperation->DefaultDragVisual != this)
	{
		if (auto* FromSlot = Cast<UInventorySlotWidget>(SlotOperation->DefaultDragVisual))
		{
			OnItemDrop.Broadcast(FromSlot, this);
			return true;
		}
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UInventorySlotWidget::SetValues(FInventoryItemInfo InItemInfo, FInventorySlot InSlot, UInventoryComponent* InInventory, UInventoryWidget* InWidget, int32 InIndex)
{
	SlotID = InIndex;
	SlotInfo = InSlot;
	ItemInfo = InItemInfo;
	InventoryRef = InInventory;
	ParentWidgetRef = InWidget;
	
	if (ToolTipWidgetClass)
	{
		USlotToolTipWidget* ToolTip = CreateWidget<USlotToolTipWidget>(GetWorld(), ToolTipWidgetClass);
		ToolTip->SetValues(ItemInfo, SlotInfo.Amount);
		SetToolTip(ToolTip);
	}
	
	AmountText->SetText(FText::FromString(FString::Printf(TEXT("x%d"), SlotInfo.Amount)));
	ItemIcon->SetBrushFromTexture(InItemInfo.Icon.LoadSynchronous());
}
