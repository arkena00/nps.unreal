#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "$ncs.unreal.prefixGameInstance.generated.h"

UCLASS()
class $ncs.unreal.api U$ncs.unreal.prefixGameInstance final : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;

    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|GameInstance")
    static FString GetVersion();

private:

};