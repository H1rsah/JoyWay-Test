// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/SphereComponent.h"
#include "JoyWay_Test/Interfaces/Damageable.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	SetRootComponent(CollisionComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CollisionComp);
	
	CollisionComp->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}


void AProjectile::Start()
{
	PrimaryActorTick.SetTickFunctionEnable(true);
	StartPosition = GetActorLocation();
}

void AProjectile::Move(const float DeltaTime)
{
	const FVector NextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;
	SetActorLocation(NextPosition, true);

	if (FVector::Dist(GetActorLocation(), StartPosition) > FireRange)
	{
		Destroy();
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& SweepResult)
{
	ApplyDamage(OtherActor, OtherComp, SweepResult, Mass * MoveSpeed * GetActorForwardVector());
	
	Destroy();
}

void AProjectile::ApplyDamage(AActor* OtherActor, UPrimitiveComponent* OtherComp, const FHitResult& Hit, const FVector& Impulse)
{
	if (OtherActor == GetInstigator())
	{
		return;
	}
    
	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(Impulse, Hit.ImpactPoint);
	}
    	
	if (OtherActor && OtherComp && OtherComp->GetCollisionObjectType() == ECC_Destructible)
	{
		OtherActor->Destroy();
	}
    	
	IDamageable* Damageable = Cast<IDamageable>(OtherActor);
	if (Damageable && GetOwner() != OtherActor)
	{
		FDamageInfo DamageInfo;
		DamageInfo.Value = Damage;
		DamageInfo.Instigator = GetInstigator();
		DamageInfo.DamageMaker = this;
		Damageable->TakeDamage(DamageInfo);
	}
}
