// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Blueprint/UserWidget.h"

AMyHUD::AMyHUD()
{
	PrimaryActorTick.bCanEverTick = false;
}

UUserWidget* AMyHUD::ShowWidget(const EWidgetsTypes WidgetType, const int32 ZOrder)
{
	HideWidget();

	CurrentWidgetType = WidgetType;

	if (const FWidgetSettings* WidgetSettings = WidgetClasses.Find(WidgetType))
	{
		const TSubclassOf<UUserWidget> ClassPtr = WidgetSettings->WidgetClass;
		if (ClassPtr && *ClassPtr)
		{
			CreateWidgetByClass(*ClassPtr,ZOrder);
			
			APlayerController* MyController = GetWorld()->GetFirstPlayerController();
			MyController->SetShowMouseCursor(WidgetSettings->ShowCursor);
			
			switch (WidgetSettings->InputMode)
			{
			default: // case EInputMode::GameOnly:
				MyController->SetInputMode(FInputModeGameOnly());
				break;
			case EInputMode::GameAndUI:
				MyController->SetInputMode(FInputModeGameAndUI().SetWidgetToFocus(CurrentWidget->TakeWidget()));
				break;
			case EInputMode::UIOnly:
				MyController->SetInputMode(FInputModeUIOnly());
				break;
			}
		}
	}

	return CurrentWidget;
}

void AMyHUD::HideWidget()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	
	ShowWidget(EWidgetsTypes::InGame);
}

UUserWidget* AMyHUD::CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder)
{
	CurrentWidget = CreateWidget(GetOwningPlayerController(), WidgetClass);
	CurrentWidget->AddToViewport(ZOrder);
	return CurrentWidget;
}
