#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "$ncs.unreal.prefixAvatarData.generated.h"

class U$ncs.unreal.prefixAbility;
class U$ncs.unreal.prefixAvatarInputData;
class A$ncs.unreal.prefixAvatar;

UCLASS(BlueprintType, Blueprintable)
class $ncs.unreal.api U$ncs.unreal.prefixAvatarData : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "$ncs.project.name")
    TArray<TSubclassOf<U$ncs.unreal.prefixAbility>> Abilities;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "$ncs.project.name")
    TArray<TSubclassOf<UGameplayEffect>> Effects;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "$ncs.project.name")
    TObjectPtr<U$ncs.unreal.prefixAvatarInputData> InputData;

protected:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("$ncs.unreal.prefixAvatarData", GetFName()); }
};