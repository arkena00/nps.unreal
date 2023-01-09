#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "$ncs.unreal.prefixPlayerState.generated.h"

UCLASS()
class $ncs.unreal.api A$ncs.unreal.prefixNVPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    A$ncs.unreal.prefixNVPlayerState();

    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|PlayerState")
    int GetTeamId() const;

    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|PlayerState")
    bool IsAlly() const;
    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|PlayerState")
    bool IsEnemy() const;

    //

    UFUNCTION(BlueprintPure, Category="$ncs.project.name|PlayerState", meta=(WorldContext="WorldContextObject"))
    static A$ncs.unreal.prefixNVPlayerState* GetNVPlayerState(const UObject* WorldContextObject);

protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void OnRep_PlayerName() override;

private:
    UPROPERTY(ReplicatedUsing = OnRep_Team)
    int TeamId = -1;
};