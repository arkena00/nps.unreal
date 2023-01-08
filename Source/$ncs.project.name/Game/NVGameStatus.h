#pragma once

UENUM(BlueprintType)
enum class ENVGameStatus : uint8 {
    Idle = 0,
    Loading,
    Loaded,
};