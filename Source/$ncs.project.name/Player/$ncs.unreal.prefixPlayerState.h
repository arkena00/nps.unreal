#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "$ncs.project.name/GAS/$ncs.unreal.prefixAttributeSet.h"
#include "$ncs.unreal.prefixPlayerState.generated.h"

class U$ncs.unreal.prefixAbilityComponent;


UCLASS()
class $ncs.unreal.api A$ncs.unreal.prefixPlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    A$ncs.unreal.prefixPlayerState();
  
      UFUNCTION(BlueprintCallable, Category = "$ncs.project.name")
    virtual U$ncs.unreal.prefixAbilityComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable, Category = "$ncs.project.name")
    U$ncs.unreal.prefixAttributeSet* GetAttributeSet() const;
    
    //

    UFUNCTION(BlueprintPure, Category = "$ncs.project.name|PlayerState", meta = (WorldContext = "WorldContextObject"))
    static A$ncs.unreal.prefixPlayerState* Get$ncs.unreal.prefixPlayerState(const UObject* WorldContextObject);

protected:

private:
    UPROPERTY()
    TObjectPtr<U$ncs.unreal.prefixAbilityComponent> $ncs.unreal.prefixAbilityComponent;
    UPROPERTY()
    TObjectPtr<U$ncs.unreal.prefixAttributeSet> $ncs.unreal.prefixAttributeSet;
};