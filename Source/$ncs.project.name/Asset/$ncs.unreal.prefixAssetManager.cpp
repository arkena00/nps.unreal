#include "$ncs.unreal.prefixAssetManager.h"
#include "AbilitySystemGlobals.h"

void U$ncs.unreal.prefixAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();

    UAbilitySystemGlobals::Get().InitGlobalData();
}

void U$ncs.unreal.prefixAssetManager::PostInitialAssetScan()
{
    Super::PostInitialAssetScan();
}

TObjectPtr<U$ncs.unreal.prefixGameData> U$ncs.unreal.prefixAssetManager::GetGameData()
{
    return GameData;
}

U$ncs.unreal.prefixAssetManager* U$ncs.unreal.prefixAssetManager::Get()
{
    return &static_cast<U$ncs.unreal.prefixAssetManager&>(UAssetManager::Get());
}

U$ncs.unreal.prefixAssetManager* U$ncs.unreal.prefixAssetManager::Get$ncs.unreal.prefixAssetManager()
{
    return Get();
}