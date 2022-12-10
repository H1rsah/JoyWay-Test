// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::TakeDamage(FDamageInfo DamageInfo)
{
	CurrentHealth -= DamageInfo.Value;

	if(CurrentHealth <= 0.f)
	{
		if(OnDie.IsBound())
		{
			OnDie.Broadcast();
		}
	}
	else
		if(OnHealthChanged.IsBound())
		{
			OnHealthChanged.Broadcast(DamageInfo.Value);
		}
	
	OnObtainDamage.Broadcast();
}


void UHealthComponent::BeginPlay()
{	
	Super::BeginPlay();
	if (CurrentHealth == 0.f)
	{
		CurrentHealth = MaxHealth;
	}
}

