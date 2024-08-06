// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShootWonBan : ModuleRules
{
	public ShootWonBan(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });
	}
}
