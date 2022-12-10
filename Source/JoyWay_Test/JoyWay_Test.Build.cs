// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JoyWay_Test : ModuleRules
{
	public JoyWay_Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "Slate", "SlateCore" });
		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
