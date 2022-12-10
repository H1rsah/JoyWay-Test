// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class AProjectile;
class UArrowComponent;
UCLASS()
class JOYWAY_TEST_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();

	void Fire();
	bool IsReadyToFire() const;
	void Cooldown();
	void Reload(int32 AmmoAmount);

	UFUNCTION(BlueprintPure)
	FText GetAmmoText() const { return FText::FromString(FString::Printf(TEXT("%d/%d"), CurrentAmmo, MaxAmmo)); };
	
	UPROPERTY(BlueprintReadWrite)
	int32 CurrentAmmo = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	int32 MaxAmmo = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Fire params")
	FName AmmoName;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire params")
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	float FireRange = 3000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Fire params")
	float Damage = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin=1), Category="Fire params")
	int32 BurstShotsAmount = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(EditCondition="BurstShotsAmount > 1", EditConditionHides, Units="Seconds"), Category="Fire params")
	float BurstTime = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(Units="Seconds"), Category="Fire params")
	float CooldownTime = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(Units="Seconds"), Category="Fire params")
	float ReloadTime = 1.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	TSubclassOf<AProjectile> ProjectileClass;

private:
	void Shot();
	void LoadAmmo();

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UArrowComponent * ProjectileSpawnPoint;

	int32 BurstShotsLeft = 0;

	FTimerHandle ReloadTimerHandle;
	FTimerHandle BurstTimerHandle;
	FTimerHandle CooldownTimerHandle;
	bool bIsReadyToFire = false;

	int32 ReloadAmount;
};
