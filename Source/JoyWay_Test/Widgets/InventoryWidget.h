// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UAmountWidget;
class USlotActionMenuWidget;
enum class EItemType : uint8;
class USizeBox;
class UTextBlock;
class UWrapBox;
class UInventorySlotWidget;
class UInventoryComponent;
/**
 * 
 */
UCLASS()
class JOYWAY_TEST_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	UFUNCTION(BlueprintCallable)
	void InitializeInventory();

	UFUNCTION()
	void OnRightClick(int32 Index);

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UAmountWidget* AmountWidget;

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UWrapBox* SlotBox;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* WeightText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	USlotActionMenuWidget* ActionMenuWidget;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventorySlotWidget> SlotWidgetClass;
	
	UPROPERTY(BlueprintReadOnly)
	UInventoryComponent* InventoryRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType DisplayByType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSortingRequired = false;

	void OnItemDropFunc(UInventorySlotWidget* From, UInventorySlotWidget* To);
};
