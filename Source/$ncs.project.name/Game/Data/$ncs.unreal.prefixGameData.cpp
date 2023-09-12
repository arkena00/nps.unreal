#include "$ncs.unreal.prefixGameData.h"

FPrimaryAssetId U$ncs.unreal.prefixGameData::GetPrimaryAssetId() const
{
    return FPrimaryAssetId("$ncs.unreal.prefixGameData", GetFName());
}