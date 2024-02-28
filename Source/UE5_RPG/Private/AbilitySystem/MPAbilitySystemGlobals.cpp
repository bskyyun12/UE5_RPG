// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MPAbilitySystemGlobals.h"
#include "MPAbilityTypes.h"

FGameplayEffectContext* UMPAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FMPGameplayEffectContext();
}