#include "NVHUD.h"

#include "NVAvatar.h"
#include "NVPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "nverse/Log.h"
#include "nverse/NVTags.h"
#include "nverse/GAS/Attribute/NVBasicAttribute.h"
#include "nverse/Subsystem/Lobby/NVLobbySystem.h"

#define INIT_ATTRIBUTE(Name) \
{ \
    FOnAttributeChangeData AttributeData; \
    AttributeData.NewValue =  NVPlayerState->GetBasicAttribute()->Name.GetCurrentValue(); \
    AttributeData.OldValue = AttributeData.NewValue; \
    On##Name##Update(AttributeData); \
}

#define MAKE_NOTIFIER(Name) \
void ANVHUD::On##Name##Update(const FOnAttributeChangeData& Data) const \
{ \
    On##Name##UpdateDelegate.Broadcast(Data.NewValue); \
}

ANVHUD::ANVHUD()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ANVHUD::Initialize()
{
    if (bInitialized) return;

    auto NVPlayerState = GetOwningPlayerController()->GetPlayerState<ANVPlayerState>();
    if (IsValid(NVPlayerState))
    {
        // Create widgets
        OnInitialize();

        // Broadcast delegates
        auto ASC = NVPlayerState->GetAbilitySystemComponent();
/*
        ASC->OnActiveGameplayEffectAddedDelegateToSelf.AddWeakLambda(this, [this, ASC](UAbilitySystemComponent* Target, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle ActiveHandle)
        {
            FGameplayTagContainer Tags;
            if (Spec.Def->UIData)
            {
                //OnAddEffectDelegate.Broadcast(Target, ActiveHandle, Spec);

                ASC->OnGameplayEffectRemoved_InfoDelegate(ActiveHandle)->AddWeakLambda(this, [this, ActiveHandle](const FGameplayEffectRemovalInfo& EffectInfo)
                {
                    //OnRemoveEffectDelegate.Broadcast(Target, ActiveHandle, EffectInfo);
                });
            }
        });*/

        bInitialized = true;
    }
}

void ANVHUD::BeginPlay()
{
    Super::BeginPlay();
}

ANVHUD* ANVHUD::GetNVHUD(const UObject* WorldContextObject)
{
    check(Cast<ANVHUD>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetHUD()));
    return Cast<ANVHUD>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetHUD());
}

void ANVHUD::OnInitialize_Implementation()
{
}