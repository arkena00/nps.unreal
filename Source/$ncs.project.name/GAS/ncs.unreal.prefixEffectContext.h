#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "$ncs.unreal.prefixEffectContext.generated.h"

USTRUCT()
struct F$ncs.unreal.prefixEffectContext : public FGameplayEffectContext
{
    GENERATED_BODY()

    virtual UScriptStruct* GetScriptStruct() const override
    {
        return F$ncs.unreal.prefixEffectContext::StaticStruct();
    }

    virtual F$ncs.unreal.prefixEffectContext* Duplicate() const override
    {
        F$ncs.unreal.prefixEffectContext* NewContext = new F$ncs.unreal.prefixEffectContext();
        *NewContext = *this;
        // Copy context data here
        NewContext->AddActors(Actors);

        return NewContext;
    }

    virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override
    {
        bOutSuccess &= Super::NetSerialize(Ar, Map, bOutSuccess);

        // Data serialization
        return true;
    }

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