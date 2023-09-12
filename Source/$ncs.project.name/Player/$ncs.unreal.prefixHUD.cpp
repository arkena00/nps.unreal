#include "$ncs.unreal.prefixHUD.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


A$ncs.unreal.prefixHUD::A$ncs.unreal.prefixHUD()
{
    PrimaryActorTick.bCanEverTick = true;
}

void A$ncs.unreal.prefixHUD::BeginPlay()
{
    Super::BeginPlay();

    if (ensure(PlayerMainWidgetClass))
    {
        PlayerMainWidget = CreateWidget(GetOwningPlayerController(), PlayerMainWidgetClass);
        PlayerMainWidget->AddToViewport();
        GetOwningPlayerController()->SetInputMode(FInputModeGameOnly{});
    }
}

A$ncs.unreal.prefixHUD* A$ncs.unreal.prefixHUD::Get$ncs.unreal.prefixHUD(const UObject* WorldContextObject)
{
    return Cast<A$ncs.unreal.prefixHUD>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetHUD());
}