#pragma once

#include "CoreMinimal.h"
#include "NVGASData.h"
#include "Engine/DataAsset.h"
#include "nverse/Dimension/NVDimensionEnum.h"
#include "nverse/Dimension/NVDimensionTypeData.h"
#include "NVGameDataAsset.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NVERSE_API UNVGameDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    const FNVDimensionTypeData& GetDimensionType(ENVDimensionType NVDimensionType);

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "nverse|DataAsset", meta=(AllowPrivateAccess=true))
    TObjectPtr<UNVGASData> GASData;
    
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "nverse|Dimension", meta=(AllowPrivateAccess=true))
    FNVDimensionTypeData ChaosDimension;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "nverse|Dimension", meta=(AllowPrivateAccess=true))
    FNVDimensionTypeData EquilibriumDimension;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "nverse|Dimension", meta=(AllowPrivateAccess=true))
    FNVDimensionTypeData NovaDimension;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "nverse|Dimension", meta=(AllowPrivateAccess=true))
    FNVDimensionTypeData ParadoxDimension;
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "nverse|Dimension", meta=(AllowPrivateAccess=true))
    FNVDimensionTypeData VoidDimension;
};

