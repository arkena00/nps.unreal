#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "$ncs.unreal.prefixEffectContext.generated.h"

USTRUCT()
struct F$ncs.unreal.prefixEffectContext : public FGameplayEffectContext
{
    GENERATED_BODY()

    virtual UScriptStruct* GetScriptStruct() const override;
    virtual F$ncs.unreal.prefixEffectContext* Duplicate() const override;
    virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

private:
    // Custom data
};

template<>
struct TStructOpsTypeTraits<F$ncs.unreal.prefixEffectContext> : public TStructOpsTypeTraitsBase2<F$ncs.unreal.prefixEffectContext>
{
    enum
    {
        WithNetSerializer = true,
        WithCopy = true
    };
};