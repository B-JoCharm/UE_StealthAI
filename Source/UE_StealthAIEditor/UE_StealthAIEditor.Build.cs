// UE_StealthAIEditor.Build.cs
using UnrealBuildTool;
using System.IO;

public class UE_StealthAIEditor : ModuleRules
{
    public UE_StealthAIEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "UE_StealthAI",
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "UnrealEd",
            "EditorScriptingUtilities",
            "LevelEditor",
            "Slate",
            "SlateCore",
            "UMG",
            "UMGEditor",
            "EditorSubsystem",
        });

        PublicIncludePaths.AddRange(new string[]
        {
            ModuleDirectory,
            Path.Combine(ModuleDirectory, "../UE_StealthAI")
        });
    }
}