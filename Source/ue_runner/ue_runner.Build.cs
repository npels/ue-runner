// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ue_runner : ModuleRules
{
	public ue_runner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
	}
}
