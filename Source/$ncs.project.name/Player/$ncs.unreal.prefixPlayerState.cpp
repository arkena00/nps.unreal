#include "$ncs.unreal.prefixPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

A$ncs.unreal.prefixPlayerState* A$ncs.unreal.prefixPlayerState::Get$ncs.unreal.prefixPlayerState(const UObject* WorldContextObject)
{
    return UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetPlayerState<A$ncs.unreal.prefixPlayerState>();
}