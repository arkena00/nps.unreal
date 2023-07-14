#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "$ncs.unreal.prefixGameMode.generated.h"

UCLASS()
class $ncs.unreal.api A$ncs.unreal.prefixGameMode final : public AGameModeBase
{
    GENERATED_BODY()

public:


protected:
    virtual void BeginPlay() override;
    virtual void StartPlay() override;

private:

};