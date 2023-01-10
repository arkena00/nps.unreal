#include "$ncs.unreal.prefixHUD.h"

#include "$ncs.unreal.prefixPlayerState.h"
#include "Kismet/GameplayStatics.h"


A$ncs.unreal.prefixHUD::A$ncs.unreal.prefixHUD()
{
    PrimaryActorTick.bCanEverTick = true;
}

void A$ncs.unreal.prefixHUD::Initialize()
{
    if (bInitialized) return;

    auto $ncs.unreal.prefixPlayerState = GetOwningPlayerController()->GetPlayerState<A$ncs.unreal.prefixPlayerState>();
    if (IsValid($ncs.unreal.prefixPlayerState))
    {
        // Create widgets
        OnInitialize();

        bInitialized = true;
    }
}

void A$ncs.unreal.prefixHUD::BeginPlay()
{
    Super::BeginPlay();
}

A$ncs.unreal.prefixHUD* A$ncs.unreal.prefixHUD::Get$ncs.unreal.prefixHUD(const UObject* WorldContextObject)
{
    return Cast<A$ncs.unreal.prefixHUD>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetHUD());
}

void A$ncs.unreal.prefixHUD::OnInitialize_Implementation()
{
}