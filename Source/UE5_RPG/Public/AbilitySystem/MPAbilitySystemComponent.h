// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MPAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAssetTagsOnEffectAppliedDelegate, const FGameplayTagContainer& /*AssetTags*/);

UCLASS()
class UE5_RPG_API UMPAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Called in AMPCharacterBase::InitAbilityActorInfo() after UAbilitySystemComponent::InitAbilityActorInfo is done.
	void OnInitAbilityActorInfo();

	FOnAssetTagsOnEffectAppliedDelegate OnReceiveAssetTagsWhenEffectAppliedToSelf;

	void AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToAdd);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

protected:
	UFUNCTION(Client, Reliable)
	void Client_OnEffectAppliedToSelf(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
