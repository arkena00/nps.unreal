#include "NVAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "NVGameDataAsset.h"

#include "nverse/Log.h"
#include "nverse/Player/NVAvatar.h"
#include "nverse/Dimension/NVDimension.h"
#include "nverse/GAS/NVEffects.h"

NVEffectsStruct NVEffects;

template<class T>
struct AlphaSortDataName
{
    AlphaSortDataName(TArray<TSubclassOf<T>> Data) {}
    bool operator()(TSubclassOf<T> A, TSubclassOf<T> B) const
    {
        return Cast<T>(A.GetDefaultObject())->GetName() > Cast<T>(B.GetDefaultObject())->GetName();
    }
};

void UNVAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();

    UAbilitySystemGlobals::Get().InitGlobalData();
}

void UNVAssetManager::PostInitialAssetScan()
{
    Super::PostInitialAssetScan();

    Initialize();
    NVEffectsStruct::Initialize(this);
}

void UNVAssetManager::Initialize()
{
    NV_LOG("Initialize NVAssetManager");
    // Clear if editor call the function again
    AvatarClasses.Reset();
    DimensionClasses.Reset();

    TSharedPtr<FStreamableHandle> GameDataAssetHandle = LoadPrimaryAssetsWithType(GameDataAssetType);
    if (GameDataAssetHandle.IsValid())
    {
        GameDataAssetHandle->WaitUntilComplete(0.f, false);
        GameData = GetPrimaryAssetObjectClass<UNVGameDataAsset>(GameDataAssetHandle->GetLoadedAsset()->GetPrimaryAssetId()).GetDefaultObject();
    }

    AvatarsHandle = LoadAssetClasses<ANVAvatar>(AvatarAssetType, AvatarClasses);
    AvatarClasses.Sort<AlphaSortDataName<ANVAvatar>>(AvatarClasses);
    NV_LOG("Loaded %d Avatars", AvatarClasses.Num());

    DimensionsHandle = LoadAssetClasses<ANVDimension>(DimensionAssetType, DimensionClasses);
    //DimensionClasses.Sort<AlphaSortDataName<ANVDimension>>(DimensionClasses);
    NV_LOG("Loaded %d Dimensions", DimensionClasses.Num());
}

ANVAvatar* UNVAssetManager::GetAvatar(const FPrimaryAssetId& PrimaryAssetId) const
{
    NV_ASSERT(PrimaryAssetId.IsValid());
    return GetPrimaryAssetObjectClass<ANVAvatar>(PrimaryAssetId).GetDefaultObject();
}

const TArray<TSubclassOf<ANVAvatar>>& UNVAssetManager::GetAvatarClasses() const
{
    return AvatarClasses;
}

TSubclassOf<ANVAvatar> UNVAssetManager::GetAvatarClassFromId(int Id) const
{
    NV_ASSERT(Id >= 0 && Id < AvatarClasses.Num());
    return AvatarClasses[Id];
}

const TArray<TSubclassOf<ANVDimension>>& UNVAssetManager::GetDimensionClasses() const
{
    return DimensionClasses;
}

const FNVDimensionTypeData& UNVAssetManager::GetDimensionType(ENVDimensionType NVDimensionType)
{
    NV_ASSERT(GameData);
    return GameData->GetDimensionType(NVDimensionType);
}

TObjectPtr<UNVGameDataAsset> UNVAssetManager::GetGameData()
{
    return GameData;
}

TObjectPtr<UNVGASData> UNVAssetManager::GetGASData()
{
    check(GameData);
    return GameData->GASData;
}

UNVAssetManager* UNVAssetManager::Get()
{
    return &static_cast<UNVAssetManager&>(UAssetManager::Get());
}

UNVAssetManager* UNVAssetManager::GetNVAssetManager()
{
    return Get();
}