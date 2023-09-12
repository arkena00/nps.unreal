#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "$ncs.unreal.prefixGameData.generated.h"

UCLASS(BlueprintType, Blueprintable)
class $ncs.unreal.api U$ncs.unreal.prefixGameData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:

protected:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};