// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UENUM()
enum class EWidgetsTypes : uint8
{
	None UMETA(DisplayName = "/"), 
	MainMenu UMETA(DisplayName = "Main Menu"),
	InGame UMETA(DisplayName = "In Game"),
	Inventory UMETA(DisplayName = "Inventory"),
	GameOver UMETA(DisplayName = "Game Over"),
	LvlChange UMETA(DisplayName = "Change Level"),

};
UENUM()
enum class EInputMode : uint8
{
	GameOnly UMETA(DisplayName = "Game Only"), 
	GameAndUI UMETA(DisplayName = "Game And UI"),
	UIOnly UMETA(DisplayName = "UI Only"),
};

USTRUCT(BlueprintType)
struct FWidgetSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	bool ShowCursor = false;
	UPROPERTY(EditDefaultsOnly)
	EInputMode InputMode;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WidgetClass;
};

/**
 * 
 */
UCLASS()
class JOYWAY_TEST_API AMyHUD : public AHUD
{
	GENERATED_BODY()
		
public:
	AMyHUD();

	UFUNCTION(BlueprintCallable)
	UUserWidget* ShowWidget(const EWidgetsTypes WidgetType, const int32 ZOrder = 0);
	UFUNCTION(BlueprintCallable)
	void HideWidget();
	UFUNCTION(BlueprintPure)
	UUserWidget* GetCurrentWidget() const { return CurrentWidget; }
	UFUNCTION(BlueprintPure)
	EWidgetsTypes GetWidgetType() const { return CurrentWidgetType; }

protected:
	virtual void BeginPlay() override;

	UUserWidget* CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder = 0);

	UPROPERTY(EditAnywhere)
	TMap<EWidgetsTypes, FWidgetSettings> WidgetClasses;
	
private:
	UPROPERTY()
	UUserWidget* CurrentWidget;
	UPROPERTY()
	EWidgetsTypes CurrentWidgetType;
};
