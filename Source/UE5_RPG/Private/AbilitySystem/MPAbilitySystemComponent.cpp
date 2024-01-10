// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MPAbilitySystemComponent.h"

void UMPAbilitySystemComponent::AbilityInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::EffectApplied);
}

void UMPAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	for (const FGameplayTag& Tag : TagContainer)
	{
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.GetTagName().ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);
	}
}