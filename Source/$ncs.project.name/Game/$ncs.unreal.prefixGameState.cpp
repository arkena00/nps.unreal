#include "$ncs.unreal.prefixGameState.h"
#include "Kismet/GameplayStatics.h"

A$ncs.unreal.prefixGameState* A$ncs.unreal.prefixGameState::Get$ncs.unreal.prefixGameState(const UObject* WorldContextObject)
{
    return Cast<A$ncs.unreal.prefixGameState>(UGameplayStatics::GetGameState(WorldContextObject));
}