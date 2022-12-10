// Copyright Epic Games, Inc. All Rights Reserved.

#include "JoyWay_TestGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Widgets/MyHUD.h"

AJoyWay_TestGameMode::AJoyWay_TestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMyHUD::StaticClass();
}
