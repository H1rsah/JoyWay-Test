// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBarWidget.generated.h"

class UHealthComponent;
/**
 * 
 */
UCLASS()
class JOYWAY_TEST_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetOwnerUnit(UHealthComponent* InComponent) { OwnerHealth = InComponent; }	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY()
	UHealthComponent* OwnerHealth;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar;
};
