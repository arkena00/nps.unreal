#include "$ncs.unreal.prefixGameInstance.h"

#include "Modules/BuildVersion.h"
#include "$ncs.project.name/Data/$ncs.unreal.prefixAssetManager.h"

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