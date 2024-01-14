// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MPAbilitySystemComponent.h"

void UMPAbilitySystemComponent::OnInitAbilityActorInfo()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::OnEffectAppliedToSelf);
}

void UMPAbilitySystemComponent::OnEffectAppliedToSelf(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	OnReceiveAssetTagsWhenEffectAppliedToSelf.Broadcast(TagContainer);
}