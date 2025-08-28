// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectChronos : ModuleRules
{
	public ProjectChronos(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AnimGraphRuntime", "AIModule", "Niagara", "UMG", "Slate", "SlateCore"});
	}
}
