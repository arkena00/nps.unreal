#include "$ncs.unreal.prefixPlayerState.h"

#include "$ncs.project.name/GAS/$ncs.unreal.prefixAbilityComponent.h"
#include "$ncs.project.name/GAS/$ncs.unreal.prefixAttributeSet.h"
#include "Kismet/GameplayStatics.h"

A$ncs.unreal.prefixPlayerState::A$ncs.unreal.prefixPlayerState()
{
    NetUpdateFrequency = 100.f;
    $ncs.unreal.prefixAbilityComponent = CreateDefaultSubobject<U$ncs.unreal.prefixAbilityComponent>("$ncs.unreal.prefixAbilityComponent");
    $ncs.unreal.prefixAttributeSet = CreateDefaultSubobject<U$ncs.unreal.prefixAttributeSet>("$ncs.unreal.prefixAttributeSet");
}

U$ncs.unreal.prefixAbilityComponent* A$ncs.unreal.prefixPlayerState::GetAbilitySystemComponent() const
{
    return $ncs.unreal.prefixAbilityComponent;
}

U$ncs.unreal.prefixAttributeSet* A$ncs.unreal.prefixPlayerState::GetAttributeSet() const
{
    return $ncs.unreal.prefixAttributeSet;
}

A$ncs.unreal.prefixPlayerState* A$ncs.unreal.prefixPlayerState::Get$ncs.unreal.prefixPlayerState(const UObject* WorldContextObject)
{
    return UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetPlayerState<A$ncs.unreal.prefixPlayerState>();
}