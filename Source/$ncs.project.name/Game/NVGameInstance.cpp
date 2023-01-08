#include "NVGameInstance.h"

#include "Modules/BuildVersion.h"
#include "nverse/Asset/NVAssetManager.h"

void UNVGameInstance::Init()
{
    Super::Init();
}

FString UNVGameInstance::GetVersion()
{
    FBuildVersion BuildVersion;
    FBuildVersion::TryRead(FBuildVersion::GetDefaultFileName(), BuildVersion);
    return NVERSE_VERSION + FString("\n") + BuildVersion.GetEngineVersion().ToString();
}