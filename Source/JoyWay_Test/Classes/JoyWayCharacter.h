// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JoyWay_Test/Interfaces/Damageable.h"
#include "JoyWayCharacter.generated.h"

class AWeaponBase;
class IInteractable;
class UInventoryComponent;
class UHealthComponent;
class UCameraComponent;
UCLASS()
class JOYWAY_TEST_API AJoyWayCharacter : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:
	AJoyWayCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable)
	void EquipWeapon(TSubclassOf<AWeaponBase> NewWeapon);
	
	UFUNCTION(BlueprintPure)
	AWeaponBase* GetCurrentWeapon() const { return CurrentWeapon; };

	UFUNCTION(BlueprintCallable)
	void GetInteractableInfo(bool& bIsInteractable, FText& ObjectName, FText& ActionName) const;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	float BaseTurnRate = 45.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Camera")
	float BaseLookUpRate = 45.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UCameraComponent* Camera;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	UInventoryComponent* InventoryComponent;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void CheckForInteractable();
	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(const FDamageInfo& DamageInfo) override;

	void OnFire();
	void OnReload();
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void TurnRight(float AxisValue);
	void LookUp(float AxisValue);
	
	UFUNCTION(BlueprintNativeEvent, Category="Health")
	void OnHealthChanged(float Damage);
	UFUNCTION(BlueprintNativeEvent, Category="Health")
	void OnDie();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interact Distance", meta=(ClampMin=0))
	float ReachDistance = 500.f;

private:
	void ToggleInventory();
	void Interact();

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	AWeaponBase* CurrentWeapon = nullptr;
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	FInventoryItemInfo WeaponInfo;

	// The interactable the player is currently looking at
	IInteractable* CurrentInteractable; 
};
