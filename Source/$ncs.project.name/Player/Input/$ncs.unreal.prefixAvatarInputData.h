#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "$ncs.unreal.prefixAvatarInputData.generated.h"

class UPlayerMappableInputConfig;
class UInputAction;
class UInputMappingContext;

UCLASS(BlueprintType, Blueprintable)
class $ncs.unreal.api U$ncs.unreal.prefixAvatarInputData : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UPlayerMappableInputConfig> Binds;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TObjectPtr<UInputMappingContext> MappingContext;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UInputAction> Move;
};