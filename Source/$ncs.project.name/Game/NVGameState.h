#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameStateBase.h"
#include "nverse/Player/NVPlayerState.h"

#include "NVGameState.generated.h"

class ANVTeam;
class ANVDimension;

UCLASS()
class NVERSE_API ANVGameState final : public AGameStateBase
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitializeDelegate);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndGameDelegate);

    //
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnterDimensionDelegate, ANVPlayerState*, NVPlayerState, const FNVDimensionData&, NVDimensionData);

    // Player
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddPlayerDelegate, const ANVPlayerState*, Player);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdatePlayersDelegate, const TArray<ANVPlayerState*>&, Players);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdatePlayerTeamDelegate, ANVPlayerState*, Player, int, TeamID);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerDie, ANVPlayerState*, Player, const FNVKillData&, KillData);

    // Team
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddTeamDelegate, ANVTeam*, Team);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateTeamsDelegate, const TArray<ANVTeam*>&, Teams);

public:
    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    void AddDimension(ANVDimension* Dimension);

    // Team
    void AddTeam();

    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    void UpdateTeamIntegrity(int TeamID, float Integrity);
    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    int GetTeamCount() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    TArray<ANVTeam*> GetTeams() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    float GetTeamIntegrity(int TeamID) const;
    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    float GetTeamIntegrityToLose(ANVPlayerState* DeadPlayer) const;

    UPROPERTY(BlueprintAssignable, Category = "nverse|GameState")
    FOnUpdateTeamsDelegate OnUpdateTeamsDelegate;

    UFUNCTION()
    void OnUpdateTeams();

    //

    UFUNCTION(NetMulticast, Reliable)
    void ClientEndGame();

    void PlayerDie(ANVPlayerState* NVPlayerState, const FNVKillData& KillData);

    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    void EnterDimension(ANVPlayerState* NVPlayerState, TSubclassOf<ANVDimension> DimensionClass);
    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    void LeaveDimension(ANVPlayerState* NVPlayerState, TSubclassOf<ANVDimension> DimensionClass);

    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    ANVDimension* GetDimension(TSubclassOf<ANVDimension> DimensionClass);
    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    TArray<ANVDimension*>& GetDimensions();

    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    TArray<ANVPlayerState*> GetAllies(bool bIgnoreSelf = true) const;
    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    TArray<ANVPlayerState*> GetEnemies() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|GameState")
    const TArray<ANVPlayerState*>& GetPlayers() const;

    //

    UFUNCTION()
    void OnUpdatePlayers();
    UFUNCTION()
    void OnAddTeam(ANVTeam* Team);

    UPROPERTY(BlueprintAssignable, Category = "nverse|GameState")
    FOnInitializeDelegate OnInitializeDelegate;

    UPROPERTY(BlueprintAssignable, Category = "nverse|GameState")
    FOnAddPlayerDelegate OnAddPlayerDelegate;
    UPROPERTY(BlueprintAssignable, Category = "nverse|GameState")
    FOnPlayerDie OnPlayerDie;
    UPROPERTY(BlueprintAssignable, Category = "nverse|GameState")
    FOnUpdatePlayersDelegate OnUpdatePlayersDelegate;
    UPROPERTY(BlueprintAssignable, Category = "nverse|GameState")
    FOnUpdatePlayerTeamDelegate OnUpdatePlayerTeamDelegate;
    UPROPERTY(BlueprintAssignable, Category = "nverse|GameState")
    FOnAddTeamDelegate OnAddTeamDelegate;

    //

    UPROPERTY(BlueprintAssignable, Category = "nverse|GameState")
    FOnEndGameDelegate OnEndGameDelegate;
    UPROPERTY(BlueprintAssignable, Category = "nverse|GameState")
    FOnEnterDimensionDelegate OnEnterDimensionDelegate;

    UFUNCTION(BlueprintPure, Category="nverse|GameState", meta=(WorldContext="WorldContextObject"))
    static ANVGameState* GetNVGameState(const UObject* WorldContextObject);

protected:
    virtual void AddPlayerState(APlayerState* PlayerState) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void HandleBeginPlay() override;
    virtual void PostNetInit() override;
    virtual void RemovePlayerState(APlayerState* PlayerState) override;

private:
    UPROPERTY()
    TObjectPtr<ULoadingTask> LoadingTask;

    UPROPERTY(Replicated)
    TArray<ANVDimension*> Dimensions;

    UPROPERTY()
    TArray<ANVTeam*> Teams;

    UPROPERTY(Transient)
    TArray<ANVPlayerState*> Players;
};