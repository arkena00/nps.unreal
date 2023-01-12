#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "$ncs.unreal.prefixOnlineSystem.generated.h"

class IOnlineSubsystem;

UCLASS(BlueprintType, Blueprintable)
class $ncs.unreal.api U$ncs.unreal.prefixOnlineSystem final : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|Online|Session")
    void CreateSession();
    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|Online|Session")
    void DestroySession();
    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|Online|Session")
    void LeaveSession();
    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|Online|Session")
    void SearchSession();
    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|Online|Session")
    void StartSession();

    class FNamedOnlineSession* GetCurrentSession() const;

    class IOnlineSubsystem* GetOSS();
    TSharedPtr<FOnlineSessionSettings> GetSettings();
    
protected:
    U$ncs.unreal.prefixOnlineSystem();
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    // Session
    void OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful);
    void OnDestroySessionCompleted(FName SessionName, bool bWasSuccessful);
    void OnFindSessionsCompleted(bool bWasSuccessful);
    void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult);
    void OnRegisterPlayersCompleted(FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& Players, bool bWasSuccessful);
    void OnSingleSessionResultCompleted(int32 LocalUserNum, bool bWasSuccessful, const FOnlineSessionSearchResult& Result);
    void OnSessionFailure(const FUniqueNetId&, ESessionFailure::Type);
    void OnSessionInviteReceived(const FUniqueNetId& UserId, const FUniqueNetId& FromId, const FString& AppId, const FOnlineSessionSearchResult& InviteResult);
    void OnSessionParticipantsUpdated(FName SessionName, const FUniqueNetId& UserId, bool JoinLeave);
    void OnSessionUserInviteAccepted(const bool bWasSuccessful, const int32 ControllerId, TSharedPtr<const FUniqueNetId> UserId, const FOnlineSessionSearchResult& InviteResult);
    void OnStartSessionCompleted(FName SessionName, bool bWasSuccessful);
    
    FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
    FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
    FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
    FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
    FOnRegisterPlayersCompleteDelegate OnRegisterPlayersCompleteDelegate;
    FOnSingleSessionResultCompleteDelegate OnSingleSessionResultCompleteDelegate;
    FOnSessionFailureDelegate OnSessionFailureDelegate;
    FOnSessionInviteReceivedDelegate OnSessionInviteReceivedDelegate;
    FOnSessionParticipantsChangeDelegate OnSessionParticipantsChangeDelegate;
    FOnSessionUserInviteAcceptedDelegate OnSessionUserInviteAcceptedDelegate;
    FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

    // Settings
    void OnSessionSettingsUpdated(FName SessionName, const FOnlineSessionSettings& InSettings);
    FOnSessionSettingsUpdatedDelegate OnSessionSettingsUpdatedDelegate;
    
private:
    FName ActiveSession;
    
    FDelegateHandle OnCreateSessionCompleteDelegateHandle;

    IOnlineSubsystem* OSS = nullptr;
    TSharedPtr<FOnlineSessionSettings> Settings;
    TSharedPtr<FOnlineSessionSearch> SearchSettings;
};