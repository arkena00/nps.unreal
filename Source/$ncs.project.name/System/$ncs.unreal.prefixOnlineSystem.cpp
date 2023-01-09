#include "$ncs.project.name/System/$ncs.unreal.prefixOnlineSystem.h"

#include "OnlineSubsystemUtils.h"
#include "$ncs.project.name/Log.h"

void U$ncs.unreal.prefixOnlineSubsystem::CreateSession()
{
    const auto SessionState = OSS->GetSessionInterface()->GetSessionState(ActiveSession);

    Settings = MakeShareable(new FOnlineSessionSettings);
    Settings->bUseLobbiesIfAvailable = true;
    Settings->NumPrivateConnections = 10;
    Settings->NumPublicConnections = 99;
    Settings->bShouldAdvertise = true;
    Settings->bAllowJoinInProgress = true;
    Settings->bIsLANMatch = false;
    Settings->bIsDedicated = false;
    Settings->bUsesStats = true;
    Settings->bAllowInvites = true;
    Settings->bUsesPresence = true;
    Settings->bAllowJoinViaPresence = true;
    Settings->bAllowJoinViaPresenceFriendsOnly = true;
    Settings->bAntiCheatProtected = false;
    Settings->BuildUniqueId = false;

    OnCreateSessionCompleteDelegateHandle = OSS->GetSessionInterface()->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
    
    OSS->GetSessionInterface()->AddOnSessionSettingsUpdatedDelegate_Handle(OnSessionSettingsUpdatedDelegate);
    OSS->GetSessionInterface()->AddOnSessionFailureDelegate_Handle(OnSessionFailureDelegate);

    bool StatusOk = OSS->GetSessionInterface()->CreateSession(0, ActiveSession, *Settings);
    if (StatusOk)
    {
        // BP_OnCreateSessionDelegate.Broadcast(ActiveSession, false);
    }
    else
    {
        OSS->GetSessionInterface()->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
    }
}

void U$ncs.unreal.prefixOnlineSubsystem::DestroySession()
{
    OSS->GetSessionInterface()->DestroySession(ActiveSession, OnDestroySessionCompleteDelegate);
}

void U$ncs.unreal.prefixOnlineSubsystem::LeaveSession()
{
    OSS->GetSessionInterface()->UnregisterPlayer(ActiveSession, *OSS->GetIdentityInterface()->GetUniquePlayerId(0));
}

void U$ncs.unreal.prefixOnlineSubsystem::SearchSession()
{
    SearchSettings = MakeShareable(new FOnlineSessionSearch);
    SearchSettings->MaxSearchResults = 999;
    SearchSettings->bIsLanQuery = false;
    SearchSettings->TimeoutInSeconds = 30;
    SearchSettings->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
    OSS->GetSessionInterface()->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
    auto State = OSS->GetSessionInterface()->FindSessions(0, SearchSettings.ToSharedRef());
}

void U$ncs.unreal.prefixOnlineSubsystem::StartSession()
{
    OSS->GetSessionInterface()->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
    OSS->GetSessionInterface()->StartSession(ActiveSession);
}

FNamedOnlineSession* U$ncs.unreal.prefixOnlineSubsystem::GetCurrentSession() const
{
    check(OSS);
    return OSS->GetSessionInterface()->GetNamedSession(ActiveSession);
}

U$ncs.unreal.prefixOnlineSubsystem::U$ncs.unreal.prefixOnlineSubsystem()
    // Session
    : OnCreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSubsystem::OnCreateSessionCompleted))
    , OnDestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSubsystem::OnDestroySessionCompleted))
    , OnFindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSubsystem::OnFindSessionsCompleted))
    , OnJoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSubsystem::OnJoinSessionCompleted))
    , OnRegisterPlayersCompleteDelegate(FOnRegisterPlayersCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSubsystem::OnRegisterPlayersCompleted))
    , OnSingleSessionResultCompleteDelegate(FOnSingleSessionResultCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSubsystem::OnSingleSessionResultCompleted))
    , OnSessionFailureDelegate(FOnSessionFailureDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSubsystem::OnSessionFailure))
    , OnSessionInviteReceivedDelegate(FOnSessionInviteReceivedDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSubsystem::OnSessionInviteReceived))
    , OnSessionParticipantsChangeDelegate(FOnSessionParticipantsChangeDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSubsystem::OnSessionParticipantsUpdated))
    , OnSessionUserInviteAcceptedDelegate(FOnSessionUserInviteAcceptedDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSubsystem::OnSessionUserInviteAccepted))
    , OnStartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSubsystem::OnStartSessionCompleted))
    // Settings
    , OnSessionSettingsUpdatedDelegate(FOnSessionSettingsUpdatedDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSubsystem::OnSessionSettingsUpdated))
    , ActiveSession("Session")
{
    OSS = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
    if (!OSS) OSS = IOnlineSubsystem::Get(NULL_SUBSYSTEM);
}

void U$ncs.unreal.prefixOnlineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (!OSS)
    {
        $ncs.unreal.prefix_error("OnlineSubsystem not found")
        return;
    }

    OSS->AddOnConnectionStatusChangedDelegate_Handle(OnConnectionStatusChangedDelegate);

    // Session
    OSS->GetSessionInterface()->AddOnSessionInviteReceivedDelegate_Handle(OnSessionInviteReceivedDelegate);
    OSS->GetSessionInterface()->AddOnSessionParticipantsChangeDelegate_Handle(OnSessionParticipantsChangeDelegate);
    OSS->GetSessionInterface()->AddOnRegisterPlayersCompleteDelegate_Handle(OnRegisterPlayersCompleteDelegate);
    OSS->GetSessionInterface()->AddOnSessionUserInviteAcceptedDelegate_Handle(OnSessionUserInviteAcceptedDelegate);
}

IOnlineSubsystem* U$ncs.unreal.prefixOnlineSubsystem::GetOSS()
{
    return OSS;
}

TSharedPtr<FOnlineSessionSettings> U$ncs.unreal.prefixOnlineSubsystem::GetSettings()
{
    return Settings;
}

void U$ncs.unreal.prefixOnlineSubsystem::OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful)
{
    OSS->GetSessionInterface()->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
    BP_OnCreateSessionDelegate.Broadcast(SessionName, bWasSuccessful);

    // Register host player after session creation
    OSS->GetSessionInterface()->TriggerOnSessionParticipantsChangeDelegates(SessionName, *OSS->GetIdentityInterface()->GetUniquePlayerId(0), true);

    // Initialize Lobby here
}

void U$ncs.unreal.prefixOnlineSubsystem::OnDestroySessionCompleted(FName SessionName, bool bWasSuccessful)
{
  // Leave Lobby here
}

void U$ncs.unreal.prefixOnlineSubsystem::OnFindSessionsCompleted(bool bWasSuccessful)
{

}

void U$ncs.unreal.prefixOnlineSubsystem::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult)
{
    // Join Lobby here
}

void U$ncs.unreal.prefixOnlineSubsystem::OnRegisterPlayersCompleted(FName SessionName, const TArray<TSharedRef<const FUniqueNetId>>& Players, bool bWasSuccessful)
{

}

void U$ncs.unreal.prefixOnlineSubsystem::OnSingleSessionResultCompleted(int32 LocalUserNum, bool bWasSuccessful,
    const FOnlineSessionSearchResult& Result)
{
}

void U$ncs.unreal.prefixOnlineSubsystem::OnSessionFailure(const FUniqueNetId&, ESessionFailure::Type FailureType)
{
}

void U$ncs.unreal.prefixOnlineSubsystem::OnSessionUserInviteAccepted(const bool bWasSuccessful, const int32 ControllerId, TSharedPtr<const FUniqueNetId> UserId,
                                                   const FOnlineSessionSearchResult& InviteResult)
{
    OSS->GetSessionInterface()->RemoveNamedSession(ActiveSession);
    OSS->GetSessionInterface()->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
    OSS->GetSessionInterface()->JoinSession(ControllerId, ActiveSession, InviteResult);
}

void U$ncs.unreal.prefixOnlineSubsystem::OnStartSessionCompleted(FName SessionName, bool bWasSuccessful)
{

}