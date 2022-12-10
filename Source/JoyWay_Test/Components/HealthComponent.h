// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JoyWay_Test/GameData/GameData.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnObtainDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Damage);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOYWAY_TEST_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	void TakeDamage(FDamageInfo DamageInfo);
	float GetHealth() const { return CurrentHealth; };
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnDie OnDie;
	UPROPERTY(BlueprintAssignable)
	FOnObtainDamage OnObtainDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHealth;
	
protected:
	virtual void BeginPlay() override;
};
