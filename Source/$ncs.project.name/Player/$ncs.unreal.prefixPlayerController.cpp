#include "$ncs.unreal.prefixPlayerController.h"

#include "Kismet/GameplayStatics.h"

A$ncs.unreal.prefixPlayerController* A$ncs.unreal.prefixPlayerController::Get$ncs.unreal.prefixPlayerController(const UObject* WorldContextObject)
{
    return Cast<A$ncs.unreal.prefixPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
}