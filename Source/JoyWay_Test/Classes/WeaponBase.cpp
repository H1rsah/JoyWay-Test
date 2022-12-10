// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

#include "Projectile.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon Mesh");
	SetRootComponent(Mesh);
	
	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>("Spawn Point");
	ProjectileSpawnPoint->SetupAttachment(Mesh);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	bIsReadyToFire = true;
}

void AWeaponBase::Fire()
{
	if(!IsReadyToFire())
		return;
	
	bIsReadyToFire = false;
	BurstShotsLeft = BurstShotsAmount;
	
	Shot();
}

bool AWeaponBase::IsReadyToFire() const
{
	return bIsReadyToFire && CurrentAmmo > 0 && BurstShotsLeft == 0;
}

void AWeaponBase::Cooldown()
{
	bIsReadyToFire = true;
}

void AWeaponBase::LoadAmmo()
{
	CurrentAmmo += ReloadAmount;
	bIsReadyToFire = true;
}

void AWeaponBase::Reload(const int32 AmmoAmount)
{
	if (AmmoAmount > 0)
	{
		bIsReadyToFire = false;
		ReloadAmount = AmmoAmount;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ThisClass::LoadAmmo, ReloadTime, false);
	}
}

void AWeaponBase::Shot()
{
	// GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green,"Fire Projectile");
	check(BurstShotsLeft > 0);
	
	if (CurrentAmmo == 0)
	{
		BurstShotsLeft = 0;
	}
	else
	{
		--CurrentAmmo;
	
		AProjectile* MyProjectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentTransform());
		MyProjectile->SetInstigator(GetInstigator());
		UGameplayStatics::FinishSpawningActor(MyProjectile,  ProjectileSpawnPoint->GetComponentTransform());
		MyProjectile->Start();

		if (FireSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		if (--BurstShotsLeft > 0)
		{
			const float NextShotTime = BurstTime / (BurstShotsAmount - 1);
			GetWorld()->GetTimerManager().SetTimer(BurstTimerHandle, this, &ThisClass::Shot, NextShotTime, false);
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &ThisClass::Cooldown, CooldownTime, false);
		}
	}
}



