// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "JoyWay_Test/Components/InventoryComponent.h"


// Sets default values
APickupActor::APickupActor()
{
	PrimaryActorTick.bCanEverTick = false;
		
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Pickup Mesh");
	Mesh->SetSimulatePhysics(true);
	SetRootComponent(Mesh);
}

void APickupActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	GenerateItemFromTable();
}

void APickupActor::SetNewItem(const FInventoryItemInfo NewItem, const int32 NewAmount)
{
	ItemInfo = NewItem;
	Amount = NewAmount;
	Mesh->SetStaticMesh(ItemInfo.Mesh.LoadSynchronous());
	Mesh->SetRelativeScale3D(ItemInfo.MeshScale);
}

void APickupActor::Interact(ACharacter* CharRef)
{
	if (CharRef)
	{
		if (UInventoryComponent* InventoryComponent = CharRef->FindComponentByClass<UInventoryComponent>())
		{
			InventoryComponent->AddItem(FInventorySlot(ItemInfo.ItemId, Amount), true);
			Destroy();
		}
	}
}

FText APickupActor::GetName()
{
	return FText::FromString(FString::Printf(TEXT("[%d] %s"), Amount, *ItemInfo.Name.ToString()));
}

void APickupActor::GenerateItemFromTable()
{
	Amount = (Amount < 1) ? 1 : Amount;

	if (Item.DataTable)
	{
		if (FInventoryItemInfo* DataRow = Item.DataTable->FindRow<FInventoryItemInfo>(Item.RowName, ""))
		{
			ItemInfo = *DataRow;
			
			Mesh->SetStaticMesh(ItemInfo.Mesh.LoadSynchronous());
			Mesh->SetRelativeScale3D(ItemInfo.MeshScale);
		}
		else
		{
			Mesh->SetStaticMesh(nullptr);
		}
	}
}
