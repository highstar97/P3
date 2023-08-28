// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class P3 : ModuleRules
{
	public P3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "UMG" });

        PrivateIncludePaths.Add("P3/Public/Buff");
        PrivateIncludePaths.Add("P3/Public/Character");
        PrivateIncludePaths.Add("P3/Public/Character/AnimInstance");
        PrivateIncludePaths.Add("P3/Public/Character/Controller");
        PrivateIncludePaths.Add("P3/Public/Component");
        PrivateIncludePaths.Add("P3/Public/Item");
        PrivateIncludePaths.Add("P3/Public/UI");
        PrivateIncludePaths.Add("P3/Public/Weapon");
    }
}
