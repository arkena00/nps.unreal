#include "$ncs.unreal.prefixGameState.h"
#include "$ncs.project.name/player/$ncs.unreal.prefixPlayerState.h"
#include "Net/UnrealNetwork.h"

void A$ncs.unreal.prefixGameState::ClientEndGame_Implementation()
{
    OnEndGameDelegate.Broadcast();
}

const TArray<A$ncs.unreal.prefixPlayerState*>& A$ncs.unreal.prefixGameState::GetPlayers() const
{
    return Players;
}

void A$ncs.unreal.prefixGameState::AddPlayerState(APlayerState* PlayerState)
{
    Super::AddPlayerState(PlayerState);
    const auto $ncs.unreal.prefixPlayerState = Cast<A$ncs.unreal.prefixPlayerState>(PlayerState);
    Players.AddUnique($ncs.unreal.prefixPlayerState);

    OnAddPlayerDelegate.Broadcast($ncs.unreal.prefixPlayerState);
}

void A$ncs.unreal.prefixGameState::RemovePlayerState(APlayerState* PlayerState)
{
    Super::RemovePlayerState(PlayerState);
    for (int i = 0; i < Players.Num(); ++i)
    {
        if (Players[i] == PlayerState)
        {
            Players.RemoveAt(i, 1);
            return;
        }
    }
}

void A$ncs.unreal.prefixGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void A$ncs.unreal.prefixGameState::HandleBeginPlay()
{
    Super::HandleBeginPlay();
}


A$ncs.unreal.prefixGameState* A$ncs.unreal.prefixGameState::Get$ncs.unreal.prefixGameState(const UObject* WorldContextObject)
{
    return Cast<A$ncs.unreal.prefixGameState>(UGameplayStatics::GetGameState(WorldContextObject));
}