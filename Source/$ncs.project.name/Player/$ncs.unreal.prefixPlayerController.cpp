#include "$ncs.unreal.prefixPlayerController.h"

#include "$ncs.unreal.prefixPlayerState.h"
#include "Kismet/GameplayStatics.h"

void A$ncs.unreal.prefixPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
    if (const auto* $ncs.unreal.prefixPlayerState = GetPlayerState<A$ncs.unreal.prefixPlayerState>())
    {
        if (auto* ASC = $ncs.unreal.prefixPlayerState->GetAbilitySystemComponent())
        {
            ASC->ProcessAbilityInput(DeltaTime, bGamePaused);
        }
    }

    Super::PostProcessInput(DeltaTime, bGamePaused);
}

A$ncs.unreal.prefixPlayerController* A$ncs.unreal.prefixPlayerController::Get$ncs.unreal.prefixPlayerController(const UObject* WorldContextObject)
{
    return Cast<A$ncs.unreal.prefixPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0));
}