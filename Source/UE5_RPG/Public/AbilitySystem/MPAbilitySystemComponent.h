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

	// WidgetController will get AssetTags(ex. Message.HealthPotion) from this and WidgetController will tell widgets 
	FOnAssetTagsOnEffectAppliedDelegate OnReceiveAssetTagsWhenEffectAppliedToSelf;

	// GiveAbility and set ability's DynamicAbilityTags using its StartupInputTag
	void AddAbility(const TSubclassOf<UGameplayAbility>& AbilityToAdd);

	// Called from MPPlayerController when input is Held
	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	// Called from MPPlayerController when input is Released
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

protected:
	/*
	* Bound with OnGameplayEffectAppliedDelegateToSelf which is called on Server.
	* We want Client RPC becuase this function broadcasts OnReceiveAssetTagsWhenEffectAppliedToSelf which is used for widgets.
	*/
	UFUNCTION(Client, Reliable)
	void Client_OnEffectAppliedToSelf(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
