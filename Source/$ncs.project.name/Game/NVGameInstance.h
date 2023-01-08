#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NVGameInstance.generated.h"

class UNVDimensionAsset;
class ANVAvatar;
class ANVDimension;

UCLASS()
class NVERSE_API UNVGameInstance final : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;

    UFUNCTION(BlueprintCallable, Category = "nverse|GameInstance")
    static FString GetVersion();

private:

};