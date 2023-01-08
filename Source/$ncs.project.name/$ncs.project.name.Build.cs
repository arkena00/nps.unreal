// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.Diagnostics;
using UnrealBuildTool;

public class nverse : ModuleRules
{
    public nverse(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Cpp20;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "InputCore", "UMG", "SlateCore",
            "EnhancedInput",
            "OnlineSubsystem", "Steamworks", "OnlineSubsystemSteam", "OnlineSubsystemUtils", "WebSockets",
            "ProceduralMeshComponent",
            "Niagara",
            "GameplayAbilities", "GameplayTags", "GameplayTasks"
        });

        var p = new Process();
        p.StartInfo.UseShellExecute = false;
        p.StartInfo.RedirectStandardOutput = true;
        p.StartInfo.FileName = "cmd.exe";
        p.StartInfo.Arguments = "/C git rev-parse --short HEAD";
        p.StartInfo.WorkingDirectory = ModuleDirectory;
        p.Start();

        var lastCommit = p.StandardOutput.ReadToEnd().Trim('\n');
        p.WaitForExit();

        PublicDefinitions.Add($"NVERSE_VERSION=\"1.0.0-dev.{lastCommit}\"");
    }
}