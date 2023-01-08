#include "NVGameState.h"

#include "NVTeam.h"
#include "GameFramework/GameSession.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "nverse/Dimension/NVDimension.h"
#include "nverse/Log.h"
#include "nverse/GAS/NVTags.h"
#include "nverse/player/NVPlayerState.h"

void ANVGameState::AddDimension(ANVDimension* Dimension)
{
    Dimensions.Add(Dimension);
}

void ANVGameState::AddTeam()
{
    FActorSpawnParameters Params;
    Params.Owner = this;
    auto Team = GetWorld()->SpawnActor<ANVTeam>(Params);
    Team->SetIntegrity(100);
    FLinearColor Color;
    static int TeamsCount = 0;
    switch (TeamsCount)
    {
    case 0: Color = FLinearColor::Blue; break;
    case 1: Color = FLinearColor::Red; break;
    case 2: Color = FLinearColor::Yellow; break;
    default: Color = FLinearColor::Black; break;
    }
    Team->SetColor(Color);
    ++TeamsCount;
}

void ANVGameState::OnAddTeam(ANVTeam* Team)
{
    Teams.Add(Team);
    OnAddTeamDelegate.Broadcast(Team);
}

void ANVGameState::OnUpdateTeams()
{
    bool bIsReplicated = true;
    for (auto Team : Teams) bIsReplicated &= IsValid(Team);
    if (bIsReplicated) OnUpdateTeamsDelegate.Broadcast(Teams);
}

void ANVGameState::ClientEndGame_Implementation()
{
    OnEndGameDelegate.Broadcast();
}

TArray<ANVDimension*>& ANVGameState::GetDimensions()
{
    return Dimensions;
}

TArray<ANVPlayerState*> ANVGameState::GetAllies(bool bIgnoreSelf) const
{
    TArray<ANVPlayerState*> Allies;
    const auto LocalPlayerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<ANVPlayerState>();
    for (auto NVPlayerState : Players)
    {
        if (bIgnoreSelf && LocalPlayerState == NVPlayerState) continue;
        if (LocalPlayerState->GetTeamID() == NVPlayerState->GetTeamID())
        {
            Allies.Add(NVPlayerState);
        }
    }
    return Allies;
}

TArray<ANVPlayerState*> ANVGameState::GetEnemies() const
{
    TArray<ANVPlayerState*> Enemies;
    const auto LocalPlayerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<ANVPlayerState>();
    for (auto NVPlayerState : Players)
    {
        if (LocalPlayerState->GetTeamID() != NVPlayerState->GetTeamID() )
        {
            Enemies.Add(NVPlayerState);
        }
    }
    return Enemies;
}

const TArray<ANVPlayerState*>& ANVGameState::GetPlayers() const
{
    return Players;
}

int ANVGameState::GetTeamCount() const
{
    return Teams.Num();
}

TArray<ANVTeam*> ANVGameState::GetTeams() const
{
    return Teams;
}

float ANVGameState::GetTeamIntegrity(int TeamID) const
{
    NV_ASSERT(TeamID < Teams.Num());
    return Teams[TeamID]->GetIntegrity();
}

ANVDimension* ANVGameState::GetDimension(TSubclassOf<ANVDimension> DimensionClass)
{
    for (ANVDimension* Dimension : Dimensions)
    {
        if (Dimension->GetClass() == DimensionClass) return Dimension;
    }

    NV_ASSERT(false); // dimension not found, check if it exists
    
    return nullptr;
}

// Authority
void ANVGameState::PlayerDie(ANVPlayerState* NVPlayerState, const FNVKillData& KillData)
{
    if (HasAuthority())
    {
        auto TeamID = NVPlayerState->GetTeamID();
        UpdateTeamIntegrity(TeamID, GetTeamIntegrity(TeamID) - GetTeamIntegrityToLose(NVPlayerState));
    }
    OnPlayerDie.Broadcast(NVPlayerState, KillData);
}

void ANVGameState::EnterDimension(ANVPlayerState* NVPlayerState, TSubclassOf<ANVDimension> DimensionClass)
{
    NVPlayerState->GetAbilitySystemComponent()->AddLooseGameplayTag(DimensionClass.GetDefaultObject()->Data.DimensionTypeTag);

    GetDimension(DimensionClass)->Enter(NVPlayerState);
}

void ANVGameState::LeaveDimension(ANVPlayerState* NVPlayerState, TSubclassOf<ANVDimension> DimensionClass)
{
    NVPlayerState->GetAbilitySystemComponent()->RemoveLooseGameplayTag(DimensionClass.GetDefaultObject()->Data.DimensionTypeTag);

    GetDimension(DimensionClass)->Leave(NVPlayerState);
}

float ANVGameState::GetTeamIntegrityToLose(ANVPlayerState* DeadPlayer) const
{
    int TeamPlayersCount = 0;
    for (const auto NVPlayerState : Players)
    {
        if (DeadPlayer->GetTeamID() == NVPlayerState->GetTeamID()) ++TeamPlayersCount;
    }
    
    return 100.f / TeamPlayersCount / 4;
}

void ANVGameState::OnUpdatePlayers()
{
    OnUpdatePlayersDelegate.Broadcast(Players);
}

void ANVGameState::UpdateTeamIntegrity(int TeamID, float Integrity)
{
    NV_ASSERT(TeamID < Teams.Num());
    Teams[TeamID]->SetIntegrity(Integrity);
    if (Teams[TeamID]->GetIntegrity() <= 0) ClientEndGame();
}

void ANVGameState::AddPlayerState(APlayerState* PlayerState)
{
    check(PlayerState);
    Super::AddPlayerState(PlayerState);
    const auto NVPlayerState = Cast<ANVPlayerState>(PlayerState);
    Players.AddUnique(NVPlayerState);

    if (NVPlayerState->IsInitialized()) OnAddPlayerDelegate.Broadcast(NVPlayerState);
    else
    {
        NVPlayerState->OnInitializeEvent.AddWeakLambda(this, [this](ANVPlayerState* NVPlayerState)
        {
            OnAddPlayerDelegate.Broadcast(NVPlayerState);
        });
    }
}

void ANVGameState::RemovePlayerState(APlayerState* PlayerState)
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

void ANVGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ANVGameState, Dimensions);
}

void ANVGameState::HandleBeginPlay()
{
    Super::HandleBeginPlay();
    
    if (HasAuthority())
    {
        OnInitializeDelegate.Broadcast();
    }
}

void ANVGameState::PostNetInit()
{
    Super::PostNetInit();
    OnInitializeDelegate.Broadcast();
}

ANVGameState* ANVGameState::GetNVGameState(const UObject* WorldContextObject)
{
    ensure(Cast<ANVGameState>(UGameplayStatics::GetGameState(WorldContextObject)));
    return Cast<ANVGameState>(UGameplayStatics::GetGameState(WorldContextObject));
}