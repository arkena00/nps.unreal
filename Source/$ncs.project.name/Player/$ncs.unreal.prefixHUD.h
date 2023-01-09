#pragma once

#include "CoreMinimal.h"
#include "$ncs.project.name/GAS/Attribute/$ncs.unreal.prefixBasicAttribute.h"
#include "GameFramework/HUD.h"
#include "$ncs.unreal.prefixHUD.generated.h"

UCLASS()
class $ncs.unreal.api A$ncs.unreal.prefixHUD : public AHUD
{
    GENERATED_BODY()

public:
    A$ncs.unreal.prefixHUD();

    void Initialize();

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintNativeEvent)
    void OnInitialize();

    UFUNCTION(BlueprintPure, Category="$ncs.project.name|HUD", meta=(WorldContext="WorldContextObject"))
    static A$ncs.unreal.prefixHUD* Get$ncs.unreal.prefixHUD(const UObject* WorldContextObject);

private:
    bool bInitialized = false;
};