#pragma once

#include "CoreMinimal.h"
#include "NVGASData.h"
#include "Engine/AssetManager.h"
#include "nverse/Dimension/NVDimensionEnum.h"
#include "nverse/Dimension/NVDimensionTypeData.h"
#include "nverse/GAS/Ability/NVAbility.h"
#include "NVAssetManager.generated.h"

class UNVGameDataAsset;
class ANVAvatar;
class ANVDimension;

UCLASS(Config = Game)
class NVERSE_API UNVAssetManager : public UAssetManager
{
    GENERATED_BODY()

public:
    inline static FPrimaryAssetType AvatarAssetType{ "Avatar" };
    inline static FPrimaryAssetType DimensionAssetType{ "Dimension" };
    inline static FPrimaryAssetType GameDataAssetType{ "NVGameDataAsset" };

    virtual void StartInitialLoading() override;
    virtual void PostInitialAssetScan() override;

    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "nverse|AssetManager")
    ANVAvatar* GetAvatar(const FPrimaryAssetId& PrimaryAssetId) const;
    UFUNCTION(BlueprintCallable, Category = "nverse|AssetManager")
    const TArray<TSubclassOf<ANVAvatar>>& GetAvatarClasses() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|AssetManager")
    TSubclassOf<ANVAvatar> GetAvatarClassFromId(int Id) const;

    UFUNCTION(BlueprintCallable, Category = "nverse|AssetManager")
    const TArray<TSubclassOf<ANVDimension>>& GetDimensionClasses() const;
    UFUNCTION(BlueprintCallable, Category = "nverse|AssetManager")
    const FNVDimensionTypeData& GetDimensionType(ENVDimensionType NVDimensionType);

    TObjectPtr<UNVGameDataAsset> GetGameData();
    TObjectPtr<UNVGASData> GetGASData();

    static UNVAssetManager* Get();

    UFUNCTION(BlueprintPure, Category="nverse|AssetManager", meta=(WorldContext="WorldContextObject"))
    static UNVAssetManager* GetNVAssetManager();

    //

private:
    TSharedPtr<FStreamableHandle> AvatarsHandle;
    TSharedPtr<FStreamableHandle> DimensionsHandle;
    TObjectPtr<UNVGameDataAsset> GameData;

    TArray<TSubclassOf<ANVAvatar>> AvatarClasses;
    TArray<TSubclassOf<ANVDimension>> DimensionClasses;


    template<class TAssetClass, class TContainer>
    TSharedPtr<FStreamableHandle> LoadAssetClasses(const FPrimaryAssetType& AssetType, TContainer& Container)
    {
        TSharedPtr<FStreamableHandle> Handle = LoadPrimaryAssetsWithType(AssetType);
        if (Handle.IsValid())
        {
            Handle->WaitUntilComplete(0.f, false);
            TArray<FPrimaryAssetId> AssetIds;
            GetPrimaryAssetIdList(AssetType, AssetIds);
            int GenId = 0;

            for (const auto& AssetId : AssetIds)
            {
                auto ObjectClass = GetPrimaryAssetObjectClass<TAssetClass>(AssetId);
                auto CDO = Cast<TAssetClass>(ObjectClass.GetDefaultObject());
                if (CDO)
                {
                    CDO->ID = GenId++;
                    Container.Add(CDO->GetClass());
                }
            }
        }
        return Handle;
    }

    template<class TAssetClass, class TContainer>
    void LoadAssetClassesAsync(const FPrimaryAssetType& AssetType, TContainer& Container)
    {
        TArray<FPrimaryAssetId> AssetIds;
        GetPrimaryAssetIdList(AssetType, AssetIds);

        LoadPrimaryAssets(AssetIds, {}, FStreamableDelegate::CreateLambda([this, AssetIds, &Container]
        {
            int GenId = 0;

            for (const auto& AssetId : AssetIds)
            {
                auto ObjectClass = GetPrimaryAssetObjectClass<TAssetClass>(AssetId);
                auto CDO = Cast<TAssetClass>(ObjectClass.GetDefaultObject());
                if (CDO)
                {
                    CDO->Data->ID = GenId++;
                    Container.Add(CDO->GetClass());
                }
            }
        }));
    }
};