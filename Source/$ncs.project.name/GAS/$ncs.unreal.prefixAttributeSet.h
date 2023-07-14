#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "$ncs.project.name/$ncs.unreal.prefixPreprocessor.h"
#include "$ncs.project.name/GAS/$ncs.unreal.prefixAbilityComponent.h"
#include "$ncs.unreal.prefixAttributeSet.generated.h"

UCLASS()
class $ncs.unreal.api U$ncs.unreal.prefixAttributeSet : public UAttributeSet
{
    GENERATED_BODY()

public:
    U$ncs.unreal.prefixAttributeSet();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

    MAKE_ATTRIBUTE_INIT(U$ncs.unreal.prefixAttributeSet)

    MAKE_ATTRIBUTE(Damage)
    UPROPERTY()
    FGameplayAttributeData Damage;

    MAKE_ATTRIBUTE(Health)
    UPROPERTY(ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& PreviousData);

    MAKE_ATTRIBUTE(HealthMax)
    UPROPERTY(ReplicatedUsing = OnRep_HealthMax)
    FGameplayAttributeData HealthMax;
    UFUNCTION()
    void OnRep_HealthMax(const FGameplayAttributeData& PreviousData);
};