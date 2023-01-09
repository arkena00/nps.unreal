#include "$ncs.unreal.prefixGameMode.h"

void A$ncs.unreal.prefixGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void A$ncs.unreal.prefixGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);
}

void A$ncs.unreal.prefixGameMode::InitGameState()
{
}

FString A$ncs.unreal.prefixGameMode::InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId,
    const FString& Options, const FString& Portal)
{
    FString Output = Super::InitNewPlayer(PlayerController, UniqueId, Options, Portal);

    return Output;
}

void A$ncs.unreal.prefixGameMode::HandleStartingNewPlayer_Implementation(APlayerController* PlayerController)
{
    const auto $ncs.unreal.prefixPlayerController = Cast<A$ncs.unreal.prefixPlayerController>(PlayerController);
    check($ncs.unreal.prefixPlayerController);
}

void A$ncs.unreal.prefixGameMode::StartPlay()
{
    Super::StartPlay();
}