#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "NVAvatar.h"
#include "NVKillData.h"
#include "Component/NVStatsComponent.h"
#include "nverse/Player/Component/NVAbilityComponent.h"
#include "GameFramework/PlayerState.h"
#include "nverse/Dimension/NVDimension.h"
#include "nverse/Subsystem/Loading/NVLoadingSystem.h"

#include "NVPlayerState.generated.h"

class UNVBasicAttribute;
UCLASS()
class NVERSE_API ANVPlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetAvatarDelegate, ANVAvatar*, Avatar);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetPlayerNameDelegate, const FString&, PlayerName);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSetTeamDelegate, ANVPlayerState*, NVPlayerState, int, TeamID);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInitializeDelegate, ANVPlayerState*, NVPlayerState);

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDie, const FNVKillData&, KillData, float, DeathDuration);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRespawn);

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnterDimensionDelegate, const FNVDimensionData&, NVDimensionData);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeaveDimensionDelegate, const FNVDimensionData&, NVDimensionData);

public:
    DECLARE_EVENT_OneParam(ANVPlayerState, FOnInitializeEvent, ANVPlayerState* NVPlayerState);

    ANVPlayerState();

    /* Force to die with killreason: cosmos */
    void Die();
    void Die(const FNVKillData& KillData);
    /* Check if the avatar should die depending on avatar's death condition */
    void CheckDeath(const FGameplayEffectModCallbackData& CallbackData);

    UFUNCTION(NetMulticast, Reliable)
    void ClientDie(const FNVKillData& KillData);
    UFUNCTION(NetMulticast, Reliable)
    void ClientReSpawn();

    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    virtual UNVAbilityComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    UNVStatsComponent* GetStatsComponent() const;

    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    void SetAvatarID(int InAvatarID);
    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    void SetTeam(int InTeamID);

    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    void EnterDimension(TSubclassOf<ANVDimension> Dimension);


    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    FNVDimensionData GetActiveDimensionData() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    ENVDimensionType GetActiveDimensionType() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    float GetTeamIntegrity() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    ANVDimension* GetOriginDimension() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    ENVDimensionType GetOriginDimensionType() const;

    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    ANVAvatar* GetAvatar() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    UNVAvatarData* GetAvatarData() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    int GetTeamID() const;

    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    bool InOrigin() const;

    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    bool IsAlly() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    bool IsDead() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    bool IsEnemy() const;

    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    bool IsInitialized() const;

    UFUNCTION(BlueprintCallable, Category = "nverse|PlayerState")
    UNVBasicAttribute* GetBasicAttribute() const;

    UFUNCTION()
    void OnEnterDimension();
    UFUNCTION()
    void OnSetAvatarID();
    UFUNCTION()
    void OnSetTeam();

    //

    FOnInitializeEvent OnInitializeEvent;

    UPROPERTY(BlueprintAssignable, Category = "nverse|PlayerState")
    FOnInitializeDelegate OnInitializeDelegate;

    UPROPERTY(BlueprintAssignable, Category = "nverse|PlayerState")
    FOnSetAvatarDelegate OnSetAvatarDelegate;
    UPROPERTY(BlueprintAssignable, Category = "nverse|PlayerState")
    FOnSetPlayerNameDelegate OnSetPlayerNameDelegate;
    UPROPERTY(BlueprintAssignable, Category = "nverse|PlayerState")
    FOnSetTeamDelegate OnSetTeamDelegate;

    UPROPERTY(BlueprintAssignable, Category = "nverse|PlayerState")
    FOnDie OnDie;
    UPROPERTY(BlueprintAssignable, Category = "nverse|PlayerState")
    FOnRespawn OnRespawn;

    UPROPERTY(BlueprintAssignable, Category = "nverse|PlayerState")
    FOnEnterDimensionDelegate OnEnterDimensionDelegate;
    UPROPERTY(BlueprintAssignable, Category = "nverse|PlayerState")
    FOnLeaveDimensionDelegate OnLeaveDimensionDelegate;

    UFUNCTION(BlueprintPure, Category="nverse|PlayerState", meta=(WorldContext="WorldContextObject"))
    static ANVPlayerState* GetNVPlayerState(const UObject* WorldContextObject);

protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void OnRep_PlayerName() override;
    virtual void PostRepNotifies() override;

private:
    bool bInitialized = false;

    UPROPERTY()
    TObjectPtr<ULoadingTask> InitializeTask;

    UPROPERTY()
    TObjectPtr<UNVAbilityComponent> NVAbilityComponent;
    UPROPERTY(Instanced, EditDefaultsOnly)
    TObjectPtr<UNVStatsComponent> NVStatsComponent;
    UPROPERTY()
    TObjectPtr<UNVBasicAttribute> BasicAttribute;

    FActiveGameplayEffectHandle DeathHandle;

    UPROPERTY(ReplicatedUsing = OnEnterDimension)
    TSubclassOf<ANVDimension> ActiveDimension;

    UPROPERTY(ReplicatedUsing = OnSetAvatarID)
    int AvatarID = -1;
    // Bug ? Replicated variables need to be after NVAbilityComponent or it will be null in NVAvatar::PossessedBy
    UPROPERTY(ReplicatedUsing = OnSetTeam)
    int TeamID = -1;
};