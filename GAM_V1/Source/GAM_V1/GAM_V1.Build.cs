// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GAM_V1 : ModuleRules
{
	public GAM_V1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate", 
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"GAM_V1",
			"GAM_V1/Variant_Horror",
			"GAM_V1/Variant_Horror/UI",
			"GAM_V1/Variant_Shooter",
			"GAM_V1/Variant_Shooter/AI",
			"GAM_V1/Variant_Shooter/UI",
			"GAM_V1/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
