#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "$ncs.unreal.prefixAbility.generated.h"

class UInputAction;

UCLASS()
class $ncs.unreal.api U$ncs.unreal.prefixAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "$ncs.project.name|Ability")
    float Cooldown;
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "$ncs.project.name|Ability", meta=(AllowPrivateAccess=true))
    FGameplayTag CooldownTag;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "$ncs.project.name|Ability")
    float Range;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "$ncs.project.name|Ability")
    TObjectPtr<UTexture2D> Image;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "$ncs.project.name|Ability")
    TObjectPtr<UInputAction> InputAction;
};