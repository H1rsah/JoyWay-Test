#pragma once

#include "Engine/DataTable.h"
#include "GameData.generated.h"

#define GET_ITEM(ID) Cast<UJoyWayGameInstance>(GetWorld()->GetGameInstance())->GetItemInfo(ID);


UENUM()
enum class EItemType : uint8
{
	Miscellaneous,
	Weapon,
	Ammo
};

class UInventorySlotWidget;
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UInventorySlotWidget* /*from*/, UInventorySlotWidget* /*to*/)

USTRUCT(BlueprintType)
struct FInventoryItemInfo : public  FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General")
	FName ItemId;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General")
	FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General")
	FText Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General")
	bool bCanBeUsed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General")
	FText UseText;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General")
	bool bCanBeStacked = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General")
	float Weight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Type")
	EItemType Type = EItemType::Miscellaneous;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	TSoftObjectPtr<UTexture2D> Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	TSoftObjectPtr<UStaticMesh> Mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	FVector MeshScale = {1,1,1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UClass* Container = nullptr;
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Amount;

	FInventorySlot() : ItemId(NAME_None), Amount(-1) {};
	FInventorySlot(FName Id, int32 ItemsAmount) : ItemId(Id), Amount(ItemsAmount) {};
};

USTRUCT(BlueprintType)
struct FStarterItemSets : public  FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FInventorySlot> Items;
};

USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Instigator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* DamageMaker;
};