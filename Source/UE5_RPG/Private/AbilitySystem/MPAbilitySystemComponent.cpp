// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MPAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MPGameplayAbility.h"

void UMPAbilitySystemComponent::OnInitAbilityActorInfo()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::Client_OnEffectAppliedToSelf);
}

void UMPAbilitySystemComponent::AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToAdd)
{
	for (const TSubclassOf<UGameplayAbility>& AbilityClass : AbilitiesToAdd)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		const UMPGameplayAbility* MPAbility = Cast<UMPGameplayAbility>(AbilitySpec.Ability);
		if (!ensure(MPAbility)) // We always want to use MPGameplayAbility
		{
			return;
		}
		AbilitySpec.DynamicAbilityTags.AddTag(MPAbility->StartupInputTag);
		GiveAbility(AbilitySpec);
	}
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