#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "$ncs.unreal.prefixPlayerState.generated.h"

UCLASS()
class $ncs.unreal.api A$ncs.unreal.prefixPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    A$ncs.unreal.prefixPlayerState();

    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|PlayerState")
    int GetTeamId() const;

    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|PlayerState")
    bool IsAlly() const;
    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|PlayerState")
    bool IsEnemy() const;

    //

    UFUNCTION(BlueprintPure, Category="$ncs.project.name|PlayerState", meta=(WorldContext="WorldContextObject"))
    static A$ncs.unreal.prefixPlayerState* Get$ncs.unreal.prefixPlayerState(const UObject* WorldContextObject);

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void OnRep_PlayerName() override;

private:
    UPROPERTY(Replicated)
    int TeamId = -1;
};