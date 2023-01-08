#include "nverse.h"

#include "GameplayTagsManager.h"
#include "Log.h"
#include "GAS/NVEffects.h"
#include "GAS/NVTags.h"
#include "Player/Component/NVStatsTags.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FNVModule, nverse, "nverse");

TMap<FGameplayTag*, FName> StrTags;

GasTags NVTag;
StatTags NVStatRoot;

void FNVModule::StartupModule()
{
    auto& Manager = UGameplayTagsManager::Get();

    NV_LOG("Load gameplay tags");

    for (auto& [TagPtr, TagName] : StrTags)
    {
        *TagPtr = Manager.AddNativeGameplayTag(TagName);
        NV_LOG("Load Tag %s %d", *TagPtr->GetTagName().ToString(), TagPtr->IsValid());
    }

    UGameplayTagsManager::Get().DoneAddingNativeTags();
}