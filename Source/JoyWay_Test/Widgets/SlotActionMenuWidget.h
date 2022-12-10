// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoyWay_Test/GameData/GameData.h"
#include "SlotActionMenuWidget.generated.h"

class UTextBlock;
class UButton;
class UInventoryWidget;
class UInventoryComponent;
/**
 * 
 */
UCLASS()
class JOYWAY_TEST_API USlotActionMenuWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void Update(int32 InIndex, UInventoryComponent* InInventory, UInventoryWidget* InWidget); 

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* UseButton;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* CancelButton;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* SplitButton;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* ThrowButton;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* ThrowText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* UseText;

private:
	UFUNCTION()
	void UseItem();
	UFUNCTION()
	void Close();
	UFUNCTION()
	void SplitStack();
	UFUNCTION()
	void ThrowAway();
	
	FInventorySlot SlotInfo;
	int32 Index;
	
	UPROPERTY()
	UInventoryComponent* InventoryRef;
	UPROPERTY()
	UInventoryWidget* ParentWidgetRef;
};
