// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DeerGame : ModuleRules
{
	public DeerGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Networking" });
	}
}
