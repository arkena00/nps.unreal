#pragma once

#include "CoreMinimal.h"
#include "$ncs.unreal.prefixPlayerController.generated.h"

UCLASS()
class $ncs.unreal.api A$ncs.unreal.prefixPlayerController final : public APlayerController
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "$ncs.unreal.prefix|PlayerController", meta = (WorldContext = "WorldContextObject"))
    static A$ncs.unreal.prefixPlayerController* Get$ncs.unreal.prefixPlayerController(const UObject* WorldContextObject);

protected:
    virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

private:

};