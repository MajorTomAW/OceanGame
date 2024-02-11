// Copyright © 2023 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CommonAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

struct FGameplayTag;

USTRUCT(BlueprintType, Blueprintable)
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	UPROPERTY(BlueprintReadOnly)
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AController* SourceController = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ACharacter* SourceCharacter = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY(BlueprintReadOnly)
	AController* TargetController = nullptr;

	UPROPERTY(BlueprintReadOnly)
	ACharacter* TargetCharacter = nullptr;
};

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class COMMONABILITYSYSTEM_API UCommonAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UCommonAttributeSet();
	
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	static void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
};
