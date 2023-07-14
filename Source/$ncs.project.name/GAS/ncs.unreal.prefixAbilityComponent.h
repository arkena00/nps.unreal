#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "$ncs.unreal.prefixAbilityComponent.generated.h"

UCLASS()
class $ncs.project.name_API U$ncs.unreal.prefixAbilityComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

public:
    U$ncs.unreal.prefixAbilityComponent();

protected:
    virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;

private:
    // Handles to abilities that had their input pressed this frame.
    TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
    // Handles to abilities that had their input released this frame.
    TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;
    // Handles to abilities that have their input held.
    TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
};