#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "$ncs.unreal.prefixEffectContext.h"
#include "$ncs.unreal.prefixAbilitySystemGlobals.generated.h"

UCLASS()
class $ncs.unreal.api U$ncs.unreal.prefixAbilitySystemGlobals : public UAbilitySystemGlobals
{
    GENERATED_BODY()

public:
    virtual F$ncs.unreal.prefixEffectContext* AllocGameplayEffectContext() const override;
    virtual void InitGameplayCueParameters(FGameplayCueParameters& CueParameters, const FGameplayEffectContextHandle& EffectContext) override;
};