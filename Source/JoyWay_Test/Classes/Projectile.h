// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
UCLASS()
class JOYWAY_TEST_API AProjectile : public AActor
{
	GENERATED_BODY()


public:
	AProjectile();
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	USphereComponent* CollisionComp;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 5000.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float FireRange = 10000.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Physics")
	float Mass = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float Damage = 1.f;

	virtual void Start();
	virtual void Move(float DeltaTime);

protected:
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& SweepResult);

	void ApplyDamage(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FHitResult& Hit, const FVector& Impulse);

private:
	FVector StartPosition;
};
