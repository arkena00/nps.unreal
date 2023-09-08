#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "$ncs.unreal.prefixAssetManager.generated.h"

class U$ncs.unreal.prefixGameData;

UCLASS(Config = Game)
class $ncs.unreal.api U$ncs.unreal.prefixAssetManager : public UAssetManager
{
    GENERATED_BODY()

public:
    inline static FPrimaryAssetType GameDataType{ "$ncs.unreal.prefixGameData" };

    virtual void StartInitialLoading() override;
    virtual void PostInitialAssetScan() override;

    TObjectPtr<U$ncs.unreal.prefixGameData> GetGameData();

    static U$ncs.unreal.prefixAssetManager* Get();

    UFUNCTION(BlueprintPure, Category = "$ncs.project.name|AssetManager", meta = (WorldContext = "WorldContextObject"))
    static U$ncs.unreal.prefixAssetManager* Get$ncs.unreal.prefixAssetManager();

    //

private:
    TObjectPtr<U$ncs.unreal.prefixGameData> GameData;
};