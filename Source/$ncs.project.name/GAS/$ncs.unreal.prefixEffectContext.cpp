#include "$ncs.unreal.prefixEffectContext.h"

UScriptStruct* F$ncs.unreal.prefixEffectContext::GetScriptStruct() const
{
    return F$ncs.unreal.prefixEffectContext::StaticStruct();
}

F$ncs.unreal.prefixEffectContext* F$ncs.unreal.prefixEffectContext::Duplicate() const
{
    F$ncs.unreal.prefixEffectContext* NewContext = new F$ncs.unreal.prefixEffectContext();
    *NewContext = *this;
    // Copy context data here
    NewContext->AddActors(Actors);

    return NewContext;
}

bool F$ncs.unreal.prefixEffectContext::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
    bOutSuccess &= Super::NetSerialize(Ar, Map, bOutSuccess);

    // Data serialization
    return true;
}