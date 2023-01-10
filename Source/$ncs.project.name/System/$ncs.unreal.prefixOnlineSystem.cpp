#include "$ncs.project.name/System/$ncs.unreal.prefixOnlineSystem.h"

#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "$ncs.project.name/Log.h"

void U$ncs.unreal.prefixOnlineSystem::CreateSession()
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

void U$ncs.unreal.prefixOnlineSystem::DestroySession()
{
    OSS->GetSessionInterface()->DestroySession(ActiveSession, OnDestroySessionCompleteDelegate);
}

void U$ncs.unreal.prefixOnlineSystem::LeaveSession()
{
    OSS->GetSessionInterface()->UnregisterPlayer(ActiveSession, *OSS->GetIdentityInterface()->GetUniquePlayerId(0));
}

void U$ncs.unreal.prefixOnlineSystem::SearchSession()
{
    SearchSettings = MakeShareable(new FOnlineSessionSearch);
    SearchSettings->MaxSearchResults = 999;
    SearchSettings->bIsLanQuery = false;
    SearchSettings->TimeoutInSeconds = 30;
    SearchSettings->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
    OSS->GetSessionInterface()->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
    auto State = OSS->GetSessionInterface()->FindSessions(0, SearchSettings.ToSharedRef());
}

void U$ncs.unreal.prefixOnlineSystem::StartSession()
{
    OSS->GetSessionInterface()->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
    OSS->GetSessionInterface()->StartSession(ActiveSession);
}

FNamedOnlineSession* U$ncs.unreal.prefixOnlineSystem::GetCurrentSession() const
{
    check(OSS);
    return OSS->GetSessionInterface()->GetNamedSession(ActiveSession);
}

U$ncs.unreal.prefixOnlineSystem::U$ncs.unreal.prefixOnlineSystem()
    // Session
    : OnCreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSystem::OnCreateSessionCompleted))
    , OnDestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSystem::OnDestroySessionCompleted))
    , OnFindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSystem::OnFindSessionsCompleted))
    , OnJoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSystem::OnJoinSessionCompleted))
    , OnRegisterPlayersCompleteDelegate(FOnRegisterPlayersCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSystem::OnRegisterPlayersCompleted))
    , OnSingleSessionResultCompleteDelegate(FOnSingleSessionResultCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSystem::OnSingleSessionResultCompleted))
    , OnSessionFailureDelegate(FOnSessionFailureDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSystem::OnSessionFailure))
    , OnSessionInviteReceivedDelegate(FOnSessionInviteReceivedDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSystem::OnSessionInviteReceived))
    , OnSessionParticipantsChangeDelegate(FOnSessionParticipantsChangeDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSystem::OnSessionParticipantsUpdated))
    , OnSessionUserInviteAcceptedDelegate(FOnSessionUserInviteAcceptedDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSystem::OnSessionUserInviteAccepted))
    , OnStartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSystem::OnStartSessionCompleted))
    // Settings
    , OnSessionSettingsUpdatedDelegate(FOnSessionSettingsUpdatedDelegate::CreateUObject(this, &U$ncs.unreal.prefixOnlineSystem::OnSessionSettingsUpdated))
    , ActiveSession("Session")
{
    OSS = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
    if (!OSS) OSS = IOnlineSubsystem::Get(NULL_SUBSYSTEM);
}

void U$ncs.unreal.prefixOnlineSystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (!OSS)
    {
        $ncs.unreal.prefix_error("OnlineSystem not found")
        return;
    }

    // Session
    OSS->GetSessionInterface()->AddOnSessionInviteReceivedDelegate_Handle(OnSessionInviteReceivedDelegate);
    OSS->GetSessionInterface()->AddOnSessionParticipantsChangeDelegate_Handle(OnSessionParticipantsChangeDelegate);
    OSS->GetSessionInterface()->AddOnRegisterPlayersCompleteDelegate_Handle(OnRegisterPlayersCompleteDelegate);
    OSS->GetSessionInterface()->AddOnSessionUserInviteAcceptedDelegate_Handle(OnSessionUserInviteAcceptedDelegate);
}

IOnlineSubsystem* U$ncs.unreal.prefixOnlineSystem::GetOSS()
{
    return OSS;
}

TSharedPtr<FOnlineSessionSettings> U$ncs.unreal.prefixOnlineSystem::GetSettings()
{
    return Settings;
}

void U$ncs.unreal.prefixOnlineSystem::OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful)
{
    OSS->GetSessionInterface()->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);

    // Register host player after session creation
    OSS->GetSessionInterface()->TriggerOnSessionParticipantsChangeDelegates(SessionName, *OSS->GetIdentityInterface()->GetUniquePlayerId(0), true);

    // Initialize Lobby here
}

void U$ncs.unreal.prefixOnlineSystem::OnDestroySessionCompleted(FName SessionName, bool bWasSuccessful)
{
  // Leave Lobby here
}

void U$ncs.unreal.prefixOnlineSystem::OnFindSessionsCompleted(bool bWasSuccessful)
{

}

void U$ncs.unreal.prefixOnlineSystem::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult)
{
    // Join Lobby here
}

void U$ncs.unreal.prefixOnlineSystem::OnRegisterPlayersCompleted(FName SessionName, const TArray<TSharedRef<const FUniqueNetId>>& Players, bool bWasSuccessful)
{

}

void U$ncs.unreal.prefixOnlineSystem::OnSingleSessionResultCompleted(int32 LocalUserNum, bool bWasSuccessful,
    const FOnlineSessionSearchResult& Result)
{
}

void U$ncs.unreal.prefixOnlineSystem::OnSessionFailure(const FUniqueNetId&, ESessionFailure::Type FailureType)
{
}

void U$ncs.unreal.prefixOnlineSystem::OnSessionUserInviteAccepted(const bool bWasSuccessful, const int32 ControllerId, TSharedPtr<const FUniqueNetId> UserId,
                                                   const FOnlineSessionSearchResult& InviteResult)
{
    OSS->GetSessionInterface()->RemoveNamedSession(ActiveSession);
    OSS->GetSessionInterface()->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
    OSS->GetSessionInterface()->JoinSession(ControllerId, ActiveSession, InviteResult);
}

void U$ncs.unreal.prefixOnlineSystem::OnStartSessionCompleted(FName SessionName, bool bWasSuccessful)
{

}

void U$ncs.unreal.prefixOnlineSystem::OnSessionInviteReceived(const FUniqueNetId& UserId, const FUniqueNetId& FromId, const FString& AppId, const FOnlineSessionSearchResult& InviteResult)
{
}

void U$ncs.unreal.prefixOnlineSystem::OnSessionParticipantsUpdated(FName SessionName, const FUniqueNetId& UserId, bool JoinLeave)
{
}

void U$ncs.unreal.prefixOnlineSystem::OnSessionSettingsUpdated(FName SessionName, const FOnlineSessionSettings& InSettings)
{
}