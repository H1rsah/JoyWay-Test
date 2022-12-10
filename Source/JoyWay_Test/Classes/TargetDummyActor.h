// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JoyWay_Test/Interfaces/Damageable.h"
#include "TargetDummyActor.generated.h"

class UObtainedDamageWidget;
class UHealthComponent;
class UWidgetComponent;
class UBoxComponent;
UCLASS()
class JOYWAY_TEST_API ATargetDummyActor : public AActor, public IDamageable
{
	GENERATED_BODY()

public:
	ATargetDummyActor();

protected:
	virtual void BeginPlay() override;

	virtual void TakeDamage(const FDamageInfo& FDamageInfo) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void OnHealthChanged(float Damage);
	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void OnDie();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* HitBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* WidgetHealthBar;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* WidgetObtainedDamage;

	UPROPERTY()
	UObtainedDamageWidget* ObtainedDamage;
};
