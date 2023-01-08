#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "NVTeam.generated.h"

UCLASS()
class ANVTeam : public AInfo
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitializeDelegate);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateIntegrityDelegate, ANVTeam*, Team, float, Integrity);

public:
    ANVTeam();
    void SetColor(FLinearColor InColor);
    void SetIntegrity(int Value);

    UFUNCTION(BlueprintCallable, Category = "nverse|Team")
    FLinearColor GetColor() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|Team")
    float GetIntegrity() const;

    UFUNCTION()
    void OnUpdateIntegrity();

    //

    UPROPERTY(BlueprintAssignable)
    FOnUpdateIntegrityDelegate OnUpdateIntegrityDelegate;
    UPROPERTY(BlueprintAssignable)
    FOnInitializeDelegate OnInitializeDelegate;

protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PostNetInit() override;

private:
    UPROPERTY(Replicated)
    FLinearColor Color;
    UPROPERTY(ReplicatedUsing = OnUpdateIntegrity)
    float Integrity;
};