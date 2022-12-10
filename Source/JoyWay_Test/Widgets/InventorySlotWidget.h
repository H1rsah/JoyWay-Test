// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotToolTipWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "JoyWay_Test/GameData/GameData.h"
#include "InventorySlotWidget.generated.h"

class UInventoryWidget;
class UInventoryComponent;
/**
 * 
 */
UCLASS()
class JOYWAY_TEST_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void SetValues(FInventoryItemInfo InItemInfo, FInventorySlot InSlot, UInventoryComponent* InInventory, UInventoryWidget* InWidget, int32 InIndex);

	FOnItemDrop OnItemDrop;

	UPROPERTY(BlueprintReadOnly)
	int32 SlotID;
	int bIsDraggable = true;
		
	UPROPERTY(BlueprintReadOnly)
	FInventorySlot SlotInfo;
	UPROPERTY(BlueprintReadOnly)
	FInventoryItemInfo ItemInfo;

	UPROPERTY()
	UInventoryComponent* InventoryRef;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Appearance")
	TSubclassOf<USlotToolTipWidget> ToolTipWidgetClass;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* ItemIcon;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* AmountText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UBorder* SlotBorder;
	
private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	UInventoryWidget* ParentWidgetRef;
};
