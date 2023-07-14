#include "$ncs.unreal.prefixAbilitySystemGlobals.h"

F$ncs.unreal.prefixEffectContext* U$ncs.unreal.prefixAbilitySystemGlobals::AllocGameplayEffectContext() const
{
    return new F$ncs.unreal.prefixEffectContext;
}

// Add custom parameters to gameplay cues
void U$ncs.unreal.prefixAbilitySystemGlobals::InitGameplayCueParameters(FGameplayCueParameters& CueParameters,
    const FGameplayEffectContextHandle& EffectContext)
{
}