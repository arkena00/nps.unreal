#include "$ncs.unreal.prefixPlayerController.h"

void A$ncs.unreal.prefixPlayerController::TryInitializeHUD() const
{
    //if (GetPawn() && HasActorBegunPlay() && GetPlayerState<A$ncs.unreal.prefixPlayerState>()) Cast<A$ncs.unreal.prefixHUD>(GetHUD())->Initialize();
}

A$ncs.unreal.prefixPlayerController* A$ncs.unreal.prefixPlayerController::Get$ncs.unreal.prefixPlayerController(const UObject* WorldContextObject)
{
    return Cast<A$ncs.unreal.prefixPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
}