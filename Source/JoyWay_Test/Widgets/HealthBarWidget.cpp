// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
#include "JoyWay_Test/Components/HealthComponent.h"

void UHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!OwnerHealth)
		return;

	HealthBar->SetPercent(OwnerHealth->CurrentHealth / OwnerHealth->MaxHealth);
}
