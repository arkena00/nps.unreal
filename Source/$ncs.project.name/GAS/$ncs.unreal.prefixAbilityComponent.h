#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "$ncs.unreal.prefixAbilityComponent.generated.h"

class U$ncs.unreal.prefixAbility;

UCLASS()
class $ncs.unreal.api U$ncs.unreal.prefixAbilityComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAttributeUpdateDelegate, float, Value);

public:
    U$ncs.unreal.prefixAbilityComponent();

    // Attribute
    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|AbilityComponent")
    void BindAttributeUpdate(FGameplayAttribute GameplayAttribute,
                             FOnAttributeUpdateDelegate OnAttributeUpdateDelegate);
    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|AbilityComponent")
    void BindAndInitAttributeUpdate(FGameplayAttribute GameplayAttribute,
                                    FOnAttributeUpdateDelegate OnAttributeUpdateDelegate);

    // Input
    void AbilityInputPressed(const U$ncs.unreal.prefixAbility* Ability);
    void ProcessAbilityInput(float DeltaTime, bool bGamePaused);

    UFUNCTION(BlueprintPure, Category="$ncs.project.name|AbilityComponent", meta = (WorldContext = "WorldContextObject"))
    static U$ncs.unreal.prefixAbilityComponent* Get$ncs.unreal.prefixAbilityComponent(const UObject* WorldContextObject);

protected:
    virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;

private:
    TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
    TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;
    TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
};