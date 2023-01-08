#pragma once

#include "nverse/player/NVPlayerController.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "nverse/Subsystem/Lobby/NVLobbyData.h"
#include "nverse/Subsystem/Lobby/NVLobbyPlayerStatus.h"
#include "NVGameMode.generated.h"

UCLASS()
class NVERSE_API ANVGameMode final : public AGameModeBase
{
    GENERATED_BODY()

public:
    AActor* FindPlayerStart(ANVPlayerState* NVPlayerState);

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
    FNVLobbyData DebugLobbyData;

protected:
    virtual void BeginPlay() override;
    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    virtual void InitGameState() override;
    virtual FString InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT(""));
    virtual void HandleStartingNewPlayer_Implementation(APlayerController* PlayerController) override;
    virtual void StartPlay() override;

private:
    UPROPERTY()
    TArray<ANVPlayerController*> PlayerControllers;
};