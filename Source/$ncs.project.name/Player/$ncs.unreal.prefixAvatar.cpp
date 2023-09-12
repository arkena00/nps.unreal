#include "$ncs.unreal.prefixAvatar.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "$ncs.unreal.prefixPlayerState.h"
#include "Avatar/$ncs.unreal.prefixAvatarData.h"
#include "Input/$ncs.unreal.prefixAvatarInputData.h"
#include "Input/$ncs.unreal.prefixInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "$ncs.project.name/GAS/$ncs.unreal.prefixAttributeSet.h"
#include "$ncs.project.name/GAS/$ncs.unreal.prefixAbility.h"

A$ncs.unreal.prefixAvatar::A$ncs.unreal.prefixAvatar()
{

}

void A$ncs.unreal.prefixAvatar::BeginPlay()
{
    Super::BeginPlay();
    TryInitialize();
}

void A$ncs.unreal.prefixAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (auto* $ncs.unreal.prefixInputComponent = CastChecked<U$ncs.unreal.prefixInputComponent>(InputComponent))
    {
        $ncs.unreal.prefixInputComponent->BindAction(Data->InputData->Move, ETriggerEvent::Triggered, this, &A$ncs.unreal.prefixAvatar::InputMove);

        for (auto AbilityClass : Data->Abilities)
        {
            $ncs.unreal.prefixInputComponent->BindAbility(AbilityClass, ETriggerEvent::Triggered, this, &A$ncs.unreal.prefixAvatar::InputAbilityTriggered);
        }
    }
}

void A$ncs.unreal.prefixAvatar::PawnClientRestart()
{
    Super::PawnClientRestart();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->ClearAllMappings();
            Subsystem->AddMappingContext(Data->InputData->MappingContext, 0);
        }
    }
}

void A$ncs.unreal.prefixAvatar::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    if (!$ncs.unreal.prefixAbilityComponent.IsValid())
    {
        if (!ensure(GetPlayerState())) return;

        $ncs.unreal.prefixAbilityComponent = GetPlayerStateChecked<A$ncs.unreal.prefixPlayerState>()->GetAbilitySystemComponent();
        $ncs.unreal.prefixAbilityComponent->InitAbilityActorInfo(GetPlayerState(), this);
    }

    InitializeAttributes();
    InitializeAbilities();
}

void A$ncs.unreal.prefixAvatar::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();
    InitializeAbilityComponent();
    TryInitialize();
}

U$ncs.unreal.prefixAbilityComponent* A$ncs.unreal.prefixAvatar::GetAbilitySystemComponent() const
{
    ensure($ncs.unreal.prefixAbilityComponent.Get());
    return $ncs.unreal.prefixAbilityComponent.Get();
}

void A$ncs.unreal.prefixAvatar::InputAbilityTriggered(const U$ncs.unreal.prefixAbility* $ncs.unreal.prefixAbility)
{
    GetAbilitySystemComponent()->AbilityInputPressed($ncs.unreal.prefixAbility);
}

void A$ncs.unreal.prefixAvatar::InputMove(const FInputActionValue& InputValue)
{
    if (Controller)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const auto Value = InputValue.Get<FVector>();

        if (Value.X != 0) AddMovementInput(FRotationMatrix{ FRotator{ 0.f, Rotation.Yaw, 0.f } }.GetUnitAxis(EAxis::Y), Value.X);
        if (Value.Y != 0) AddMovementInput(FRotationMatrix{ FRotator{ 0.f, Rotation.Yaw, 0.f } }.GetUnitAxis(EAxis::X), Value.Y);
    }
}

void A$ncs.unreal.prefixAvatar::InitializeAbilities()
{
    $ncs.unreal.prefixAbilityComponent->ClearAllAbilities();
    for (auto AbilityClass : Data->Abilities)
    {
        $ncs.unreal.prefixAbilityComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass));
    }

    const auto& EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
    for (auto Effect : Data->Effects)
    {
        $ncs.unreal.prefixAbilityComponent->ApplyGameplayEffectToSelf(Effect->GetDefaultObject<UGameplayEffect>(), 1, EffectContext);
    }
}

void A$ncs.unreal.prefixAvatar::InitializeAbilityComponent()
{
    check(Cast<A$ncs.unreal.prefixPlayerState>(GetPlayerState()));

    if (!$ncs.unreal.prefixAbilityComponent.IsValid())
    {
        $ncs.unreal.prefixAbilityComponent = Cast<A$ncs.unreal.prefixPlayerState>(GetPlayerState())->GetAbilitySystemComponent();
        $ncs.unreal.prefixAbilityComponent->InitAbilityActorInfo(GetPlayerState(), this);
    }
}

void A$ncs.unreal.prefixAvatar::InitializeAttributes()
{
    const auto AttributeSet = Cast<A$ncs.unreal.prefixPlayerState>(GetPlayerState())->GetAttributeSet();
    AttributeSet->InitHealthMax(100);
    AttributeSet->InitHealth(100);
}

void A$ncs.unreal.prefixAvatar::TryInitialize()
{
    if (IsLocallyControlled() && !bInitialized && GetPlayerState() && HasActorBegunPlay())
    {
        bInitialized = true;
    }
}

A$ncs.unreal.prefixAvatar* A$ncs.unreal.prefixAvatar::GetA$ncs.unreal.prefixAvatar(const UObject* WorldContextObject)
{
  return Cast<A$ncs.unreal.prefixAvatar>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)->GetPawn());
}