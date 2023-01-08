#include "$ncs.unreal.prefixPlayerController.h"

void A$ncs.unreal.prefixPlayerController::TryInitializeHUD() const
{
    //if (GetPawn() && HasActorBegunPlay() && GetPlayerState<ANVPlayerState>()) Cast<ANVHUD>(GetHUD())->Initialize();
}

A$ncs.unreal.prefixPlayerController* ANVPlayerController::Get$ncs.unreal.prefixPlayerController(const UObject* WorldContextObject)
{
    ensure(Cast<A$ncs.unreal.prefixPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)));
    return Cast<A$ncs.unreal.prefixPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
}