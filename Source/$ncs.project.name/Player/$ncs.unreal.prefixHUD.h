#pragma once

#include "CoreMinimal.h"
#include "nverse/GAS/Attribute/NVBasicAttribute.h"
#include "GameFramework/HUD.h"
#include "NVHUD.generated.h"

UCLASS()
class NVERSE_API ANVHUD : public AHUD
{
    GENERATED_BODY()

    //DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAddEffectDelegate, UAbilitySystemComponent*, ASC, FActiveGameplayEffectHandle, ActiveGameplayEffectHandle, const FGameplayEffectSpec&, GameplayEffectSpec);
    //DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRemoveEffectDelegate, UAbilitySystemComponent*, ASC, FActiveGameplayEffectHandle, ActiveGameplayEffectHandle, const FGameplayEffectRemovalInfo&, GameplayEffectRemovalInfo);

public:
    ANVHUD();

    void Initialize();
/*
    UPROPERTY(BlueprintAssignable, Category = "nverse|HUD")
    FOnAddEffectDelegate OnAddEffectDelegate;
    UPROPERTY(BlueprintAssignable, Category = "nverse|HUD")
    FOnRemoveEffectDelegate OnRemoveEffectDelegate;*/

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintNativeEvent)
    void OnInitialize();

    UFUNCTION(BlueprintPure, Category="nverse|HUD", meta=(WorldContext="WorldContextObject"))
    static ANVHUD* GetNVHUD(const UObject* WorldContextObject);

private:
    bool bInitialized = false;
};