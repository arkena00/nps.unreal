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
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    virtual void InitGameState() override;
    virtual FString InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT(""));
    virtual void HandleStartingNewPlayer_Implementation(APlayerController* PlayerController) override;
    virtual void StartPlay() override;

private:

};