#include "NVPlayerState.h"

#include "GameplayEffectExtension.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "nverse/Log.h"
#include "nverse/Asset/NVAssetManager.h"
#include "nverse/Dimension/NVDimension.h"
#include "nverse/game/NVGameState.h"
#include "nverse/GAS/NVEffects.h"
#include "nverse/GAS/Attribute/NVBasicAttribute.h"
#include "nverse/NVTags.h"

ANVPlayerState::ANVPlayerState()
{
    bAlwaysRelevant = true;

    NetUpdateFrequency = 100.0f;
    NVAbilityComponent = CreateDefaultSubobject<UNVAbilityComponent>(FName("AbilityComponent"));
    NVStatsComponent = CreateDefaultSubobject<UNVStatsComponent>(FName("StatsComponent"));

    BasicAttribute = CreateDefaultSubobject<UNVBasicAttribute>(TEXT("AttributeBasic"));

    bUseCustomPlayerNames = true;

    InitializeTask = CreateDefaultSubobject<ULoadingTask>(FName("LoadingTask"));
    InitializeTask->SetSource(this);
    InitializeTask->SetOnComplete([this]{ OnInitializeEvent.Broadcast(this); OnInitializeDelegate.Broadcast(this); });
    InitializeTask->SetCount(3);

    NVAbilityComponent->RegisterGameplayTagEvent(NVTag.State.Dead).AddWeakLambda(this, [this](const FGameplayTag Tag, int32 Count)
    {
        if (Count == 0) ClientReSpawn();
    });
}

void ANVPlayerState::Die()
{
    FNVKillData KillData;
    KillData.Source = nullptr; // todo use the last player who dealt damage ?
    KillData.Target = this;
    KillData.Reason = ENVKillReason::Cosmos;
    KillData.ForceKill = true;
    Die(KillData);
}

void ANVPlayerState::Die(const FNVKillData& KillData)
{
    check(HasAuthority());
    if (GetAbilitySystemComponent()->HasMatchingGameplayTag(NVTag.State.Dead)) return;

    // Try to die, notify abilities that could counter death (can apply effects that will affect the GE_Death)
    if (!KillData.ForceKill)
    {
        FGameplayEventData EventData;
        EventData.Target = this;
        GetAbilitySystemComponent()->HandleGameplayEvent(NVTag.Event.Player.Die_Begin, &EventData);
    }

    DeathHandle = GetAbilitySystemComponent()->ApplyEffect(NVEffects.State.Death);

    // Check if death tag was applied or if we should force the kill
    if (GetAbilitySystemComponent()->HasMatchingGameplayTag(NVTag.State.Dead) || KillData.ForceKill)
    {
        if (KillData.Source && KillData.Source != KillData.Target)
        {
            KillData.Source->GetStatsComponent()->Update_Add(NVStat.Combat.Kill, 1, true);
        }
        GetStatsComponent()->Update_Add(NVStat.Combat.Death, 1, true);

        //float DeathDuration;
        //NVEffects.State.Death.GetDefaultObject()->DurationMagnitude.GetStaticMagnitudeIfPossible(1, DeathDuration);
        GetAbilitySystemComponent()->CancelAllAbilities();

        ClientDie(KillData);
    }
}

void ANVPlayerState::CheckDeath(const FGameplayEffectModCallbackData& CallbackData)
{
    check(HasAuthority());

    check(Cast<ANVPlayerState>(CallbackData.Target.GetOwnerActor()) == this);
    if (GetAvatar()->ShouldDie())
    {
        const auto SourcePlayer = Cast<ANVPlayerState>(CallbackData.EffectSpec.GetContext().GetOriginalInstigator());
        const auto TargetPlayer = Cast<ANVPlayerState>(CallbackData.Target.GetOwnerActor());

        FNVKillData KillData;
        KillData.Source = SourcePlayer;
        KillData.Target = TargetPlayer;
        KillData.Reason = ENVKillReason::Player;

        if (BasicAttribute->GetIntegrity() <= 0) KillData.Reason = ENVKillReason::Integrity;

        Die(KillData);
    }
}

void ANVPlayerState::ClientDie_Implementation(const FNVKillData& KillData)
{
    Cast<ANVAvatar>(GetAvatar())->Die();
    OnDie.Broadcast(KillData, 10);
    Cast<ANVGameState>(GetWorld()->GetGameState())->PlayerDie(this, KillData);
}

void ANVPlayerState::ClientReSpawn_Implementation()
{
    Cast<ANVAvatar>(GetAvatar())->Spawn();
    OnRespawn.Broadcast();

}

void ANVPlayerState::BeginPlay()
{
    Super::BeginPlay();
}


void ANVPlayerState::EnterDimension(TSubclassOf<ANVDimension> Dimension)
{
    NV_ASSERT(Dimension);

    FGameplayEventData EventData;
    EventData.Instigator = this;
    GetAbilitySystemComponent()->HandleGameplayEvent(NVTag.Event.Player.EnterDimension_Begin, &EventData);

    if (HasAuthority())
    {
        // give 20 void energy when a player goes to a dimension he doesn't enter yet, +10 energy / kill
        if (ActiveDimension == Dimension) return;

        const auto NVGameState = Cast<ANVGameState>(GetWorld()->GetGameState());
        NV_OASSERT(NVGameState);

        if (ActiveDimension)
        {
            NVGameState->LeaveDimension(this, ActiveDimension);
            OnLeaveDimensionDelegate.Broadcast(ActiveDimension.GetDefaultObject()->Data);
        }

        NVGameState->EnterDimension(this, Dimension);
        ActiveDimension = Dimension;

        OnEnterDimension();
    }
}

void ANVPlayerState::SetTeam(int InTeamID)
{
    TeamID = InTeamID;
    OnSetTeam();
}

FNVDimensionData ANVPlayerState::GetActiveDimensionData() const
{
    return ActiveDimension.GetDefaultObject()->Data;
}

ENVDimensionType ANVPlayerState::GetActiveDimensionType() const
{
    if (!ActiveDimension) return ENVDimensionType::None;
    return ActiveDimension.GetDefaultObject()->Data.Type;
}

float ANVPlayerState::GetTeamIntegrity() const
{
    return Cast<ANVGameState>(GetWorld()->GetGameState())->GetTeamIntegrity(GetTeamID());
}

ANVDimension* ANVPlayerState::GetOriginDimension() const
{
    check(Cast<ANVAvatar>(GetPawn()));
    return Cast<ANVAvatar>(GetPawn())->Data->Origin.GetDefaultObject();
}

ENVDimensionType ANVPlayerState::GetOriginDimensionType() const
{
    return GetOriginDimension()->Data.Type;
}

ANVAvatar* ANVPlayerState::GetAvatar() const
{
    return Cast<ANVAvatar>(GetPawn()); // null when range limit is reached, UE destroy it
}

UNVAvatarData* ANVPlayerState::GetAvatarData() const
{
    return UNVAssetManager::Get()->GetAvatarClassFromId(AvatarID).GetDefaultObject()->Data.Get();
}

int ANVPlayerState::GetTeamID() const
{
    return TeamID;
}

bool ANVPlayerState::InOrigin() const
{
    return GetOriginDimensionType() == GetActiveDimensionType();
}

bool ANVPlayerState::IsAlly() const
{
    return !IsEnemy();
}

bool ANVPlayerState::IsDead() const
{
    return false;
}

bool ANVPlayerState::IsEnemy() const
{
    return GetWorld()->GetFirstPlayerController()->GetPlayerState<ANVPlayerState>()->GetTeamID() != GetTeamID();
}

bool ANVPlayerState::IsInitialized() const
{
    return InitializeTask->IsComplete();
}

UNVAbilityComponent* ANVPlayerState::GetAbilitySystemComponent() const
{
    return NVAbilityComponent;
}

UNVStatsComponent* ANVPlayerState::GetStatsComponent() const
{
    return NVStatsComponent;
}

void ANVPlayerState::SetAvatarID(int InAvatarID)
{
    AvatarID = InAvatarID;
    OnSetAvatarID();
}

UNVBasicAttribute* ANVPlayerState::GetBasicAttribute() const
{
    return BasicAttribute;
}

void ANVPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ANVPlayerState, ActiveDimension);
    DOREPLIFETIME(ANVPlayerState, AvatarID);
    DOREPLIFETIME(ANVPlayerState, TeamID);
}

void ANVPlayerState::OnRep_PlayerName()
{
    Super::OnRep_PlayerName();
    OnSetPlayerNameDelegate.Broadcast(GetPlayerName());
    if (!GetPlayerName().IsEmpty())
    {
        OnSetPlayerNameDelegate.Broadcast(GetPlayerName());
        InitializeTask->Update(1);
    }
}

void ANVPlayerState::PostRepNotifies()
{
    Super::PostRepNotifies();
}

void ANVPlayerState::OnSetTeam()
{
    OnSetTeamDelegate.Broadcast(this, TeamID);
    InitializeTask->Update(0);
}

void ANVPlayerState::OnEnterDimension()
{
    GetBasicAttribute()->SetIntegrity(100);
    OnEnterDimensionDelegate.Broadcast(GetActiveDimensionData());
}

void ANVPlayerState::OnSetAvatarID()
{
    auto AvatarClass = UNVAssetManager::Get()->GetAvatarClassFromId(AvatarID);
    OnSetAvatarDelegate.Broadcast(AvatarClass.GetDefaultObject());
    InitializeTask->Update(2);
}

ANVPlayerState* ANVPlayerState::GetNVPlayerState(const UObject* WorldContextObject)
{
    ensure(UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetPlayerState<ANVPlayerState>());
    return UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetPlayerState<ANVPlayerState>();
}