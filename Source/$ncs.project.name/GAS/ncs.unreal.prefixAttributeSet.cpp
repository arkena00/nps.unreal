#include "$ncs.unreal.prefixAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

U$ncs.unreal.prefixAttributeSet::U$ncs.unreal.prefixAttributeSet()
{

}

void U$ncs.unreal.prefixAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(U$ncs.unreal.prefixAttributeSet, Health);
    DOREPLIFETIME(U$ncs.unreal.prefixAttributeSet, HealthMax);
}

void U$ncs.unreal.prefixAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& Value)
{
    Super::PreAttributeChange(Attribute, Value);

    if (Attribute == GetHealthAttribute())
    {
        Value = FMath::Clamp<float>(Value, 0.f, GetHealthMax());
    }
}

void U$ncs.unreal.prefixAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    const auto InputDamage = GetDamage();
    SetDamage(0);

    if (Data.EvaluatedData.Attribute == GetDamageAttribute())
    {
        SetHealth(GetHealth() - InputDamage);
    }
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(GetHealth() - InputDamage);
    }

    // const auto TargetPlayer = Data.Target.GetOwner();
    // TargetPlayer->CheckDeath(Data);
}

MAKE_ATTRIBUTE_DEF(U$ncs.unreal.prefixAttributeSet, Health);
MAKE_ATTRIBUTE_DEF(U$ncs.unreal.prefixAttributeSet, HealthMax);