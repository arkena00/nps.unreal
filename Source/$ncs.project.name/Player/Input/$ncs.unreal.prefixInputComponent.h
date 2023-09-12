#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "$ncs.project.name/GAS/$ncs.unreal.prefixAbility.h"
#include "$ncs.unreal.prefixInputComponent.generated.h"

UCLASS(Config = Input)
class U$ncs.unreal.prefixInputComponent : public UEnhancedInputComponent
{
    GENERATED_BODY()

public:
    template<class FuncType, class UserClass, typename... VarTypes>
    FEnhancedInputActionEventBinding& BindAbility(const TSubclassOf<U$ncs.unreal.prefixAbility> AbilityClass, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, VarTypes... Vars)
    {
        const U$ncs.unreal.prefixAbility* Ability = AbilityClass.GetDefaultObject();
        return BindAction(Ability->InputAction, TriggerEvent, Object, Func, Ability);
    }
};