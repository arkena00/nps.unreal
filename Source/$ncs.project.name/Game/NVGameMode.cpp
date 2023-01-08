#include "nverse/Game/NVGameMode.h"

#include "EngineUtils.h"
#include "NVGameState.h"
#include "nverse/player/NVPlayerState.h"
#include "NVGameInstance.h"
#include "GameFramework/PlayerStart.h"
#include "nverse/Log.h"

#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "nverse/Asset/NVAssetManager.h"
#include "nverse/Dimension/NVDimension.h"
#include "nverse/player/NVAvatar.h"
#include "nverse/Subsystem/Lobby/NVLobbySystem.h"
#include "nverse/World/NVPlayerStart.h"

void ANVGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void ANVGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);
    GetGameInstance()->GetSubsystem<UNVLobbySystem>()->InitializePIELobby(DebugLobbyData);
}

void ANVGameMode::InitGameState()
{
    Super::InitGameState();
    #if WITH_EDITOR
        if(!GetWorld()->IsGameWorld()) return;
    #endif
    
    // add dimensions
    for (auto DimensionClass : UNVAssetManager::Get()->GetDimensionClasses())
    {
        const auto Dimension = GetWorld()->SpawnActor<ANVDimension>(DimensionClass);
        GetGameState<ANVGameState>()->AddDimension(Dimension);
        NV_LOG("[Server] Spawn dimension %s", *Dimension->Data.Name.ToString());
    }

    // add teams
    auto TeamCount = GetGameInstance()->GetSubsystem<UNVLobbySystem>()->GetLobbyData().Teams.Num();
    for (int i = 0; i < TeamCount; ++i)
    {
        GetGameState<ANVGameState>()->AddTeam();
    }
}

FString ANVGameMode::InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId,
    const FString& Options, const FString& Portal)
{
    FString Output = Super::InitNewPlayer(PlayerController, UniqueId, Options, Portal);
    
    GetGameInstance()->GetSubsystem<UNVLobbySystem>()->UpdatePlayerLoadingStatus(UniqueId, ENVLobbyPlayerLoadingStatus::GameConnected);

    return Output;
}

void ANVGameMode::HandleStartingNewPlayer_Implementation(APlayerController* PlayerController)
{
    const auto NVPlayerController = Cast<ANVPlayerController>(PlayerController);
    check(NVPlayerController);
    PlayerControllers.Add(NVPlayerController);

    // Initialize player
    const auto LobbyPlayerData = GetGameInstance()->GetSubsystem<UNVLobbySystem>()->GetPlayerData(NVPlayerController);
    const auto NVPlayerSate = NVPlayerController->GetPlayerState<ANVPlayerState>();
    NVPlayerSate->SetAvatarID(LobbyPlayerData.SelectedAvatar);
    NVPlayerSate->SetPlayerName(LobbyPlayerData.Name);
    NVPlayerSate->SetTeam(LobbyPlayerData.TeamIndex);
    NV_LOG("[Server] Initialize Player %s", *LobbyPlayerData.Name);

    // Make players enter the first dimension
    auto Dimensions = GetGameState<ANVGameState>()->GetDimensions();
    NV_ASSERT(Dimensions.Num() > 0);

    const auto AvatarClass = UNVAssetManager::Get()->GetAvatarClassFromId(LobbyPlayerData.SelectedAvatar);
    NV_LOG("[Server] Spawn Avatar %s", *AvatarClass->GetName());
    FActorSpawnParameters ActorSpawnParameters;
    ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    const auto PlayerStart = FindPlayerStart(NVPlayerSate);
    const auto SpawnLocation = PlayerStart ? PlayerStart->GetTransform() : FTransform();
    ANVAvatar* PlayerAvatar = Cast<ANVAvatar>(GetWorld()->SpawnActorAbsolute(AvatarClass, SpawnLocation, ActorSpawnParameters));
    PlayerController->Possess(PlayerAvatar);
    NVPlayerSate->EnterDimension(Dimensions[0]->GetClass());
    NV_LOG("[Server] Player enter dimension %s", *Dimensions[0]->Data.Name.ToString());
}

void ANVGameMode::StartPlay()
{
    // World loaded, initialize the server on the new world
    GetGameInstance()->GetSubsystem<UNVLobbySystem>()->InitializeServer();
    
    Super::StartPlay();
}


AActor* ANVGameMode::FindPlayerStart(ANVPlayerState* NVPlayerState)
{
    // Choose a player start
    APlayerStart* FoundPlayerStart = nullptr;
    UClass* PawnClass = GetDefaultPawnClassForController(NVPlayerState->GetPlayerController());
    APawn* PawnToFit = PawnClass ? PawnClass->GetDefaultObject<APawn>() : nullptr;
    TArray<APlayerStart*> UnOccupiedStartPoints;
    TArray<APlayerStart*> OccupiedStartPoints;
    UWorld* World = GetWorld();
    for (TActorIterator<ANVPlayerStart> It(World); It; ++It)
    {
        ANVPlayerStart* NVPlayerStart = *It;
        const int PlayerTeamID = NVPlayerState->GetTeamID();

        FVector ActorLocation = NVPlayerStart->GetActorLocation();
        const FRotator ActorRotation = NVPlayerStart->GetActorRotation();
        if (!World->EncroachingBlockingGeometry(PawnToFit, ActorLocation, ActorRotation))
        {
            if (PlayerTeamID == NVPlayerStart->GetTeamID())
            {
                FoundPlayerStart = NVPlayerStart;
                break;
            }
        }
    }

    return FoundPlayerStart;
}