#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "$ncs.unreal.prefixGameState.generated.h"

UCLASS()
class $ncs.unreal.api A$ncs.unreal.prefixGameState final : public AGameStateBase
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndGameDelegate);

public:
    UPROPERTY(BlueprintAssignable, Category = "$ncs.project.name|GameState")
    FOnEndGameDelegate OnEndGameDelegate;

    UFUNCTION(BlueprintPure, Category = "$ncs.project.name|GameState", meta = (WorldContext = "WorldContextObject"))
    static A$ncs.unreal.prefixGameState* Get$ncs.unreal.prefixGameState(const UObject* WorldContextObject);
};