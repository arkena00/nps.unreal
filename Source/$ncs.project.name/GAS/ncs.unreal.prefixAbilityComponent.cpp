#include "$ncs.unreal.prefixAbilityComponent.h"

U$ncs.unreal.prefixAbilityComponent::U$ncs.unreal.prefixAbilityComponent()
{
    SetIsReplicated(true);
    ReplicationMode = EGameplayEffectReplicationMode::Full;
}

void U$ncs.unreal.prefixAbilityComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
    Super::AbilitySpecInputPressed(Spec);

    // We don't support UGameplayAbility::bReplicateInputDirectly.
    // Use replicated events instead so that the WaitInputPress ability task works.
    if (Spec.IsActive())
    {
        // Invoke the InputPressed event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
        InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
    }
}