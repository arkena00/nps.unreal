#include "$ncs.unreal.prefixGameInstance.h"

#include "Modules/BuildVersion.h"

void U$ncs.unreal.prefixGameInstance::Init()
{
    Super::Init();
}

FString U$ncs.unreal.prefixGameInstance::GetVersion()
{
    FBuildVersion BuildVersion;
    FBuildVersion::TryRead(FBuildVersion::GetDefaultFileName(), BuildVersion);
    return BUILD_VERSION + FString("\n") + BuildVersion.GetEngineVersion().ToString();
}