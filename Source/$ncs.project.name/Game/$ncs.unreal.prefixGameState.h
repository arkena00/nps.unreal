#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "$ncs.project.name/Player/$ncs.unreal.prefixPlayerState.h"
#include "$ncs.unreal.prefixGameState.generated.h"

UCLASS()
class $ncs.unreal.api A$ncs.unreal.prefixGameState final : public AGameStateBase
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndGameDelegate);

    // Player
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddPlayerDelegate, const A$ncs.unreal.prefixPlayerState*, Player);

public:

    UFUNCTION(NetMulticast, Reliable)
    void ClientEndGame();

    //

    UPROPERTY(BlueprintAssignable, Category = "$ncs.project.name|GameState")
    FOnAddPlayerDelegate OnAddPlayerDelegate;

    //

    UPROPERTY(BlueprintAssignable, Category = "$ncs.project.name|GameState")
    FOnEndGameDelegate OnEndGameDelegate;
    UPROPERTY(BlueprintAssignable, Category = "$ncs.project.name|GameState")
    FOnEnterDimensionDelegate OnEnterDimensionDelegate;

    UFUNCTION(BlueprintPure, Category="$ncs.project.name|GameState", meta=(WorldContext="WorldContextObject"))
    static A$ncs.unreal.prefixGameState* GetNVGameState(const UObject* WorldContextObject);

protected:
    virtual void AddPlayerState(APlayerState* PlayerState) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void HandleBeginPlay() override;
    virtual void RemovePlayerState(APlayerState* PlayerState) override;

private:
    UPROPERTY(Transient)
    TArray<A$ncs.unreal.prefixPlayerState*> Players;
};