#pragma once

DECLARE_LOG_CATEGORY_EXTERN(Log$ncs.project.name, Log, All);

#define $ncs.project.prefix_log(message, ...) UE_LOG(Log$ncs.project.name, Display, TEXT(message), __VA_ARGS__)
#define $ncs.project.prefix_warning(message, ...) UE_LOG(Log$ncs.project.name, Warning, TEXT(message), __VA_ARGS__)
#define $ncs.project.prefix_error(message, ...) UE_LOG(Log$ncs.project.name, Error, TEXT(message), __VA_ARGS__)

#define $ncs.project.prefix_glog(message, ...) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT(message), __VA_ARGS__));