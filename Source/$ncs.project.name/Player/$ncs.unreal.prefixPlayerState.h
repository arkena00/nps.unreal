#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "$ncs.unreal.prefixPlayerState.generated.h"

UCLASS()
class $ncs.unreal.api A$ncs.unreal.prefixPlayerState : public APlayerState
{
    GENERATED_BODY()

public:

    //

    UFUNCTION(BlueprintPure, Category="$ncs.project.name|PlayerState", meta=(WorldContext="WorldContextObject"))
    static A$ncs.unreal.prefixPlayerState* Get$ncs.unreal.prefixPlayerState(const UObject* WorldContextObject);

protected:

private:

};