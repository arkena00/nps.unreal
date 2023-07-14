using System;
using System.Diagnostics;
using UnrealBuildTool;

public class $ncs.project.name : ModuleRules
{
    public $ncs.project.name(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Cpp20;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "InputCore", "UMG", "SlateCore"
            , "EnhancedInput"
            , "GameplayAbilities", "GameplayTags", "GameplayTasks"
            , "Niagara"
        });

        // build version
        var p = new Process();
        p.StartInfo.UseShellExecute = false;
        p.StartInfo.RedirectStandardOutput = true;
        p.StartInfo.FileName = "cmd.exe";
        p.StartInfo.Arguments = "/C git rev-parse --short HEAD";
        p.StartInfo.WorkingDirectory = ModuleDirectory;
        p.Start();

        var lastCommit = p.StandardOutput.ReadToEnd().Trim('\n');
        p.WaitForExit();

        PublicDefinitions.Add($"BUILD_VERSION=\"1.0.0-dev.{lastCommit}\"");
    }
}