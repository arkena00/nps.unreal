#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "GSEffectContext.h"
#include "GSAbilitySystemGlobals.generated.h"

UCLASS()
class $ncs.project.name_API UGSAbilitySystemGlobals : public UAbilitySystemGlobals
{
    GENERATED_BODY()

public:
    virtual FGSEffectContext* AllocGameplayEffectContext() const override;
    virtual void InitGameplayCueParameters(FGameplayCueParameters& CueParameters, const FGameplayEffectContextHandle& EffectContext) override;
};