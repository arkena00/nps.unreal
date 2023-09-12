#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "$ncs.unreal.prefixHUD.generated.h"

UCLASS()
class $ncs.unreal.api A$ncs.unreal.prefixHUD : public AHUD
{
    GENERATED_BODY()

public:
    A$ncs.unreal.prefixHUD();

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintPure, Category = "$ncs.project.name|HUD", meta = (WorldContext = "WorldContextObject"))
    static A$ncs.unreal.prefixHUD* Get$ncs.unreal.prefixHUD(const UObject* WorldContextObject);

    //

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "$ncs.project.name")
    TSubclassOf<UUserWidget> PlayerMainWidgetClass;

private:
    UPROPERTY()
    UUserWidget* PlayerMainWidget = nullptr;
};