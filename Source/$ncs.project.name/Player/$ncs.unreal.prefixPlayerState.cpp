#include "$ncs.unreal.prefixPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

A$ncs.unreal.prefixPlayerState::A$ncs.unreal.prefixPlayerState()
{
    bAlwaysRelevant = true;
}

int A$ncs.unreal.prefixPlayerState::GetTeamId() const
{
    return TeamId;
}

bool A$ncs.unreal.prefixPlayerState::IsAlly() const
{
    return !IsEnemy();
}

bool A$ncs.unreal.prefixPlayerState::IsEnemy() const
{
    return GetWorld()->GetFirstPlayerController()->GetPlayerState<A$ncs.unreal.prefixPlayerState>()->GetTeamId() != GetTeamId();
}

void A$ncs.unreal.prefixPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(A$ncs.unreal.prefixPlayerState, TeamId);
}

void A$ncs.unreal.prefixPlayerState::OnRep_PlayerName()
{
    Super::OnRep_PlayerName();
}

A$ncs.unreal.prefixPlayerState* A$ncs.unreal.prefixPlayerState::Get$ncs.unreal.prefixPlayerState(const UObject* WorldContextObject)
{
    return UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetPlayerState<A$ncs.unreal.prefixPlayerState>();
}