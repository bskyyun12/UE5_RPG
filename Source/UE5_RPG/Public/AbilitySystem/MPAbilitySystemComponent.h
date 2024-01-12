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
	void BindEffectAppliedToSelfEvent();

	FOnAssetTagsOnEffectAppliedDelegate OnReceiveAssetTagsWhenEffectAppliedToSelf;

protected:
	UFUNCTION()
	void OnEffectAppliedToSelf(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

};
