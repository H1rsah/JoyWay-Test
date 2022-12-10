// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JoyWay_Test/GameData/GameData.h"
#include "SlotToolTipWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class JOYWAY_TEST_API USlotToolTipWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetValues(FInventoryItemInfo InItem, int32 InAmount);

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* ItemIcon;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* NameText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* TypeText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* DescriptionText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* SummaryWeightText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* WeightText;
	
	UPROPERTY(BlueprintReadOnly)
	FInventoryItemInfo ItemInfo;
	UPROPERTY(BlueprintReadOnly)
	int32 Amount;
};
