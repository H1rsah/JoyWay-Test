// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JoyWay_Test/GameData/GameData.h"
#include "JoyWay_Test/Interfaces/Interactable.h"
#include "PickupActor.generated.h"

class UBoxComponent;
UCLASS()
class JOYWAY_TEST_API APickupActor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	APickupActor();
	void SetNewItem(const FInventoryItemInfo NewItem, const int32 NewAmount);

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Interact(ACharacter* CharRef) override;
	virtual FText GetName() override;
	virtual FText GetAction() override { return FText::FromString("Pickup"); };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category="Item Settings")
	FDataTableRowHandle Item;
	
	UPROPERTY(BlueprintReadOnly)
	FInventoryItemInfo ItemInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true, ClampMin = 1), Category="Item Settings")
	int32 Amount;

private:
	void GenerateItemFromTable();	
};
