// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MPAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MPGameplayAbility.h"

void UMPAbilitySystemComponent::OnInitAbilityActorInfo()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::Client_OnEffectAppliedToSelf);
}

void UMPAbilitySystemComponent::AddAbility(const TSubclassOf<UGameplayAbility>& AbilityToAdd)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityToAdd, 1);
	const UMPGameplayAbility* MPAbility = Cast<UMPGameplayAbility>(AbilitySpec.Ability);
	if (!ensure(MPAbility)) // We always want to use MPGameplayAbility
	{
		return;
	}

	/*
	* TODO: Implement Swapping, removing tags so player can freely switch skills in skill slots.
	* The idea here is to change DynamicAbilityTags in runtime. DynamicAbilityTags is responsible for activating abilities.
	* So, we will re-assign a new InputTag for the ability.
	*/
	AbilitySpec.DynamicAbilityTags.AddTag(MPAbility->StartupInputTag);
	GiveAbility(AbilitySpec);
}

void UMPAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UMPAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UMPAbilitySystemComponent::Client_OnEffectAppliedToSelf_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	OnReceiveAssetTagsWhenEffectAppliedToSelf.Broadcast(TagContainer);
}