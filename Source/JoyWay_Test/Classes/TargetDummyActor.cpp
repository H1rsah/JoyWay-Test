// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetDummyActor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "JoyWay_Test/Components/HealthComponent.h"
#include "JoyWay_Test/Widgets/HealthBarWidget.h"
#include "JoyWay_Test/Widgets/ObtainedDamageWidget.h"


ATargetDummyActor::ATargetDummyActor()
{
	PrimaryActorTick.bCanEverTick = false;

	HitBox = CreateDefaultSubobject<UBoxComponent>("Hit Box");
	SetRootComponent(HitBox);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Mesh->SetupAttachment(HitBox);

	WidgetHealthBar = CreateDefaultSubobject<UWidgetComponent>("Health Bar");
	WidgetHealthBar->SetupAttachment(HitBox);

	WidgetObtainedDamage = CreateDefaultSubobject<UWidgetComponent>("Obtained Damage");
	WidgetObtainedDamage->SetupAttachment(HitBox);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
	HealthComponent->OnDie.AddDynamic(this, &ThisClass::OnDie);

}

void ATargetDummyActor::BeginPlay()
{
	Super::BeginPlay();

	ObtainedDamage = Cast<UObtainedDamageWidget>(WidgetObtainedDamage->GetUserWidgetObject());
	
	if (UHealthBarWidget* Health = Cast<UHealthBarWidget>(WidgetHealthBar->GetUserWidgetObject()))
	{
		Health->SetOwnerUnit(HealthComponent);
		WidgetHealthBar->SetVisibility(true);
	}
}

void ATargetDummyActor::TakeDamage(const FDamageInfo& FDamageInfo)
{
	HealthComponent->TakeDamage(FDamageInfo);
	
	if (ObtainedDamage)
	{
		ObtainedDamage->Refresh(FDamageInfo.Value);
	}
}

void ATargetDummyActor::OnDie_Implementation()
{
	Destroy();
}

void ATargetDummyActor::OnHealthChanged_Implementation(float Damage)
{
}

