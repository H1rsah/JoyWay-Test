// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JoyWay_Test/GameData/GameData.h"
#include "JoyWayGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class JOYWAY_TEST_API UJoyWayGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FInventoryItemInfo GetItemInfo(const FName ItemId) const { return *ItemsData->FindRow<FInventoryItemInfo>(ItemId, ""); };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* ItemsData;
};
