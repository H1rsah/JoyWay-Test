// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyWayCharacter.h"

#include "WeaponBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "JoyWay_Test/Components/HealthComponent.h"
#include "JoyWay_Test/Components/InventoryComponent.h"
#include "JoyWay_Test/Interfaces/Interactable.h"
#include "JoyWay_Test/Widgets/InventoryWidget.h"
#include "JoyWay_Test/Widgets/MyHUD.h"


AJoyWayCharacter::AJoyWayCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->InitCapsuleSize(50.f, 96.0f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->bUsePawnControlRotation = true;

	GetMesh()->bCastDynamicShadow = false;
	GetMesh()->CastShadow = false;
	GetMesh()->SetupAttachment(Camera);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory component"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
	HealthComponent->OnDie.AddDynamic(this, &ThisClass::OnDie);
}

void AJoyWayCharacter::EquipWeapon(TSubclassOf<AWeaponBase> NewWeapon)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
	}

	if (NewWeapon)
	{
		FActorSpawnParameters Params;
		Params.Instigator = this;
		Params.Owner = this;
		CurrentWeapon = GetWorld()->SpawnActor<AWeaponBase>(NewWeapon, GetMesh()->GetSocketTransform("GripPoint"), Params);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GripPoint");
	}
}


void AJoyWayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ThisClass::OnFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ThisClass::OnReload);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ThisClass::Interact);
	PlayerInputComponent->BindAction("ToggleInventory", IE_Pressed, this, &ThisClass::ToggleInventory);

	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ThisClass::TurnRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ThisClass::LookUp);
}

void AJoyWayCharacter::GetInteractableInfo(bool& bIsInteractable, FText& ObjectName, FText& ActionName) const
{
	if (CurrentInteractable)
	{
		bIsInteractable = true;
		ObjectName =  CurrentInteractable->GetName();
		ActionName = CurrentInteractable->GetAction();
		return;
	}
	
	bIsInteractable = false;
	ObjectName = FText::GetEmpty();
}

void AJoyWayCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AJoyWayCharacter::TakeDamage(const FDamageInfo& DamageInfo)
{
	HealthComponent->TakeDamage(DamageInfo);
}

void AJoyWayCharacter::OnFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Fire();
	}
}

void AJoyWayCharacter::OnReload()
{
	if (CurrentWeapon)
	{
		const int32 AmmoRequired = CurrentWeapon->MaxAmmo - CurrentWeapon->CurrentAmmo;
		int32 Result;
		InventoryComponent->RemoveItemAmount(CurrentWeapon->AmmoName, AmmoRequired, false, Result);
		CurrentWeapon->Reload(Result);
	}
}

void AJoyWayCharacter::MoveForward(float AxisValue)
{
	if (AxisValue != 0.f)
	{
		AddMovementInput(GetActorForwardVector(), AxisValue);
	}
}

void AJoyWayCharacter::MoveRight(float AxisValue)
{
	if (AxisValue != 0.f)
	{
		AddMovementInput(GetActorRightVector(), AxisValue);
	}
}

void AJoyWayCharacter::TurnRight(float AxisValue)
{
	AddControllerYawInput(AxisValue * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AJoyWayCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AJoyWayCharacter::OnDie_Implementation() {}
void AJoyWayCharacter::OnHealthChanged_Implementation(float Damage) {}

void AJoyWayCharacter::CheckForInteractable()
{
	FHitResult Hit;

	// Initialize the query params to ignore the character
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(
		Hit,
		Camera->GetComponentLocation(),
		Camera->GetForwardVector() * ReachDistance + Camera->GetComponentLocation(),
		ECC_WorldDynamic,
		Params);
	// DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Blue, false, 0, 0, 1.f);

	if(IInteractable* PotentialInteractable = Cast<IInteractable>(Hit.GetActor()))
	{
		CurrentInteractable = PotentialInteractable;
		return;
	}
	CurrentInteractable = nullptr;
}

void AJoyWayCharacter::ToggleInventory()
{
	// Toggle Inventory based on HUD state
	if (AMyHUD* CurrentHUD = Cast<AMyHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		if (CurrentHUD->GetWidgetType() == EWidgetsTypes::InGame)
		{
			CurrentHUD->ShowWidget(EWidgetsTypes::Inventory);
		}
		else
		{
			CurrentHUD->ShowWidget(EWidgetsTypes::InGame);					
		}
	}
}

void AJoyWayCharacter::Interact()
{
	if (CurrentInteractable)
	{
		CurrentInteractable->Interact(this);
	}
}
