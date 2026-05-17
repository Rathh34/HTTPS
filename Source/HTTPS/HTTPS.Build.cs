using UnrealBuildTool;
using System.IO;

public class HTTPS : ModuleRules
{
	public HTTPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG",
			"Slate",
			"SlateCore",
			"AIModule",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[]
		{
			Path.Combine(ModuleDirectory, "Core"),
			Path.Combine(ModuleDirectory, "Data"),
			Path.Combine(ModuleDirectory, "Components"),
			Path.Combine(ModuleDirectory, "Buildings"),
			Path.Combine(ModuleDirectory, "Natives"),
			Path.Combine(ModuleDirectory, "Deposits"),
			Path.Combine(ModuleDirectory, "UI")
		});
	}
}