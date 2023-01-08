#include "NVTeam.h"

#include "NVGameState.h"
#include "Net/UnrealNetwork.h"

ANVTeam::ANVTeam()
{
    bReplicates = true;
    bAlwaysRelevant = true;
}

void ANVTeam::SetColor(FLinearColor InColor)
{
    Color = InColor;
}

void ANVTeam::BeginPlay()
{
    Super::BeginPlay();
    Cast<ANVGameState>(GetWorld()->GetGameState())->OnAddTeam(this);
}

void ANVTeam::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ANVTeam, Color);
    DOREPLIFETIME(ANVTeam, Integrity);
}

void ANVTeam::PostNetInit()
{
    Super::PostNetInit();
    OnInitializeDelegate.Broadcast();
}

void ANVTeam::SetIntegrity(int Value)
{
    Integrity = Value;
    if (HasAuthority()) OnUpdateIntegrity();
}

FLinearColor ANVTeam::GetColor() const
{
    return Color;
}

float ANVTeam::GetIntegrity() const
{
    return Integrity;
}

void ANVTeam::OnUpdateIntegrity()
{
    OnUpdateIntegrityDelegate.Broadcast(this, Integrity);
}