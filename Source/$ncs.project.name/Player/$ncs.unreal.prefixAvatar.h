#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "$ncs.project.name/GAS/$ncs.unreal.prefixAbilityComponent.h"
#include "$ncs.unreal.prefixAvatar.generated.h"

class U$ncs.unreal.prefixAbility;
class U$ncs.unreal.prefixAbilityComponent;
class U$ncs.unreal.prefixAvatarData;

UCLASS()
class $ncs.unreal.api A$ncs.unreal.prefixAvatar : public ACharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    A$ncs.unreal.prefixAvatar();

    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name|Avatar")
    virtual U$ncs.unreal.prefixAbilityComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintPure, Category = "$ncs.project.name|Avatar", meta = (WorldContext = "WorldContextObject"))
    static A$ncs.unreal.prefixAvatar* GetA$ncs.unreal.prefixAvatar(const UObject* WorldContextObject);

    //

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "$ncs.project.name|Avatar")
    TObjectPtr<UZTAvatarData> Data;

protected:
    virtual void BeginPlay() override;
    virtual void PawnClientRestart() override;
    virtual void PossessedBy(AController* NewController) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void OnRep_PlayerState() override;

    void InputAbilityTriggered(const U$ncs.unreal.prefixAbility* $ncs.unreal.prefixAbility);
    void InputMove(const FInputActionValue& InputValue);

    void InitializeAbilities();
    void InitializeAbilityComponent();
    void InitializeAttributes();
    void TryInitialize();

private:
    bool bInitialized = false;
    TWeakObjectPtr<U$ncs.unreal.prefixAbilityComponent> $ncs.unreal.prefixAbilityComponent;
};