#pragma once

// attributes
#define MAKE_ATTRIBUTE_INIT(ClassName) using MakeAttributeClassName = ClassName;

#define MAKE_ATTRIBUTE(PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(MakeAttributeClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define MAKE_ATTRIBUTE_DEF(ClassName, PropertyName) \
void ClassName::OnRep_##PropertyName(const FGameplayAttributeData& PreviousData) \
{ \
GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, PropertyName, PreviousData); \
}