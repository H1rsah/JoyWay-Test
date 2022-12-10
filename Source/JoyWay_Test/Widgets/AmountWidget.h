// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmountWidget.generated.h"

class USlider;
class UTextBlock;
class UButton;
class UInventoryComponent;
/**
 * 
 */
UCLASS()
class JOYWAY_TEST_API UAmountWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void Update(int32 InIndex, UInventoryComponent* InInventory);

protected:
	UFUNCTION(BlueprintCallable)
	void Close();
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* OKButton;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* MaxValueText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	USlider* AmountSlider;
	
private:
	UPROPERTY()
	UInventoryComponent* InventoryRef;
	int32 Index;
};
