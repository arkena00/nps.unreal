#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "$ncs.unreal.prefixAvatar.generated.h"

class UGameplayAbility;
class U$ncs.unreal.prefixAbilityComponent;
UCLASS()
class $ncs.project.name_API A$ncs.unreal.prefixAvatar : public ACharacter
{
    GENERATED_BODY()

public:
    A$ncs.unreal.prefixAvatar();

    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name")
    void InitializeAbilities();
    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name")
    void InitializeAttributes();

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void PawnClientRestart() override;
    virtual void PossessedBy(AController* NewController) override;

private:
    TObjectPtr<UInputMappingContext> InputMappingContext;
    TWeakObjectPtr<U$ncs.unreal.prefixAbilityComponent> $ncs.unreal.prefixAbilityComponent;
};