#include "$ncs.unreal.prefixAbilityComponent.h"
#include "$ncs.unreal.prefixAbility.h"
#include "Kismet/GameplayStatics.h"
#include "$ncs.project.name/Player/$ncs.unreal.prefixPlayerState.h"

U$ncs.unreal.prefixAbilityComponent::U$ncs.unreal.prefixAbilityComponent()
{
    SetIsReplicated(true);
    ReplicationMode = EGameplayEffectReplicationMode::Mixed;
}

void U$ncs.unreal.prefixAbilityComponent::BindAttributeUpdate(FGameplayAttribute GameplayAttribute,
    FOnAttributeUpdateDelegate OnAttributeUpdateDelegate)
{
    GetGameplayAttributeValueChangeDelegate(GameplayAttribute).AddWeakLambda(this, [OnAttributeUpdateDelegate](const FOnAttributeChangeData& Data)
    {
        OnAttributeUpdateDelegate.ExecuteIfBound(Data.NewValue);
    });
}

void U$ncs.unreal.prefixAbilityComponent::BindAndInitAttributeUpdate(FGameplayAttribute GameplayAttribute,
    FOnAttributeUpdateDelegate OnAttributeUpdateDelegate)
{
    BindAttributeUpdate(GameplayAttribute, OnAttributeUpdateDelegate);
    OnAttributeUpdateDelegate.Execute(GetNumericAttribute(GameplayAttribute));
}

void U$ncs.unreal.prefixAbilityComponent::AbilityInputPressed(const U$ncs.unreal.prefixAbility* Ability)
{
    for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
    {
        if (AbilitySpec.Ability == Ability)
        {
            InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
            InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
        }
    }
}

void U$ncs.unreal.prefixAbilityComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
    Super::AbilitySpecInputPressed(Spec);

    if (Spec.IsActive())
    {
        InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
    }
}

void U$ncs.unreal.prefixAbilityComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
    static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
    AbilitiesToActivate.Reset();

    //
    // Process all abilities that activate when the input is held.
    //
    for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
    {
        if (const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
        {
            if (AbilitySpec->Ability && !AbilitySpec->IsActive())
            {
                const auto NVAbilityCDO = CastChecked<U$ncs.unreal.prefixAbility>(AbilitySpec->Ability);

                //if (NVAbilityCDO->GetInputActivationType() == ENVInputActivationType::WhileInputActive)
                {
                    //AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
                }
            }
        }
    }

    //
    // Process all abilities that had their input pressed this frame.
    //
    for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
    {
        if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
        {
            if (AbilitySpec->Ability)
            {
                AbilitySpec->InputPressed = true;

                if (AbilitySpec->IsActive())
                {
                    // Ability is active so pass along the input event.
                    AbilitySpecInputPressed(*AbilitySpec);
                }
                else
                {
                    const auto NVAbilityCDO = CastChecked<U$ncs.unreal.prefixAbility>(AbilitySpec->Ability);

                    //if (NVAbilityCDO->GetInputActivationType() == ENVInputActivationType::OnInputTriggered)
                    {
                        AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
                    }
                }
            }
        }
    }

    //
    // Try to activate all the abilities that are from presses and holds.
    // We do it all at once so that held inputs don't activate the ability
    // and then also send a input event to the ability because of the press.
    //
    for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate)
    {
        TryActivateAbility(AbilitySpecHandle);
    }

    //
    // Process all abilities that had their input released this frame.
    //
    for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles)
    {
        if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
        {
            if (AbilitySpec->Ability)
            {
                AbilitySpec->InputPressed = false;

                if (AbilitySpec->IsActive())
                {
                    // Ability is active so pass along the input event.
                    AbilitySpecInputReleased(*AbilitySpec);
                }
            }
        }
    }

    //
    // Clear the cached ability handles.
    //
    InputPressedSpecHandles.Reset();
    InputReleasedSpecHandles.Reset();
}

U$ncs.unreal.prefixAbilityComponent* U$ncs.unreal.prefixAbilityComponent::Get$ncs.unreal.prefixAbilityComponent(const UObject* WorldContextObject)
{
    check(UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetPlayerState<A$ncs.unreal.prefixPlayerState>());
    return UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetPlayerState<A$ncs.unreal.prefixPlayerState>()->GetAbilitySystemComponent();
}