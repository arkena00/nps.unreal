#include "$ncs.unreal.prefixAvatar.h"

#include "EnhancedInputSubsystems.h"
#include "$ncs.unreal.prefixPlayerState.h"
#include "$ncs.project.name/GAS/$ncs.unreal.prefixAttributeSet.h"

A$ncs.unreal.prefixAvatar::A$ncs.unreal.prefixAvatar()
{

}

void A$ncs.unreal.prefixAvatar::InitializeAbilities()
{
    $ncs.unreal.prefixAbilityComponent->ClearAllAbilities();
    $ncs.unreal.prefixAbilityComponent->GiveAbility(FGameplayAbilitySpec(Ability));
}

void A$ncs.unreal.prefixAvatar::InitializeAttributes()
{
    const auto AttributeSet = Cast<A$ncs.unreal.prefixPlayerState>(GetPlayerState())->GetAttributeSet();
    AttributeSet->InitHealthMax(100);
    AttributeSet->InitHealth(100);
}

void A$ncs.unreal.prefixAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void A$ncs.unreal.prefixAvatar::PawnClientRestart()
{
    Super::PawnClientRestart();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->ClearAllMappings();
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }
}

void A$ncs.unreal.prefixAvatar::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    if (!$ncs.unreal.prefixAbilityComponent.IsValid())
    {
        $ncs.unreal.prefixAbilityComponent = GetPlayerStateChecked<A$ncs.unreal.prefixPlayerState>()->GetAbilitySystemComponent();
        $ncs.unreal.prefixAbilityComponent->InitAbilityActorInfo(GetPlayerState(), this);
    }

    InitializeAttributes();
    InitializeAbilities();
}