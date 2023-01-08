#include "NVGameDataAsset.h"

#include "nverse/Log.h"

const FNVDimensionTypeData& UNVGameDataAsset::GetDimensionType(ENVDimensionType NVDimensionType)
{
    switch (NVDimensionType)
    {
    case ENVDimensionType::Chaos: return ChaosDimension;
    case ENVDimensionType::Equilibrium: return EquilibriumDimension;
    case ENVDimensionType::Nova: return NovaDimension;
    case ENVDimensionType::Paradox: return ParadoxDimension;
    case ENVDimensionType::Void: return VoidDimension;
    default: ensure(false); return VoidDimension;
    }
}