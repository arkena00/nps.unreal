#include "$ncs.project.name.h"

#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(F$ncs.unreal.prefixModule, $ncs.project.name, "$ncs.project.name");

void FNVModule::StartupModule()
{
    auto& Manager = UGameplayTagsManager::Get();

    // Manager.AddNativeGameplayTag(TagName);

    UGameplayTagsManager::Get().DoneAddingNativeTags();
}