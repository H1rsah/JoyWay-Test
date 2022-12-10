// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObtainedDamageWidget.generated.h"

/**
 * 
 */
UCLASS()
class JOYWAY_TEST_API UObtainedDamageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Refresh(float DamageAmount);
};
