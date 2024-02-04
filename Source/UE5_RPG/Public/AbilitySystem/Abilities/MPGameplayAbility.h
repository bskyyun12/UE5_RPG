// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MPGameplayAbility.generated.h"

UCLASS()
class UE5_RPG_API UMPGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	/*
	* This is just to give a start input tag that will be set for ability's DynamicAbilityTags
	* DynamicAbilityTags is responsible for activating abilities and could be changed in runtime.
	*/
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	FScalableFloat Damage;
};
