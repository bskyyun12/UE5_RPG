// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MPPlayerState.h"
#include "AbilitySystem/MPAbilitySystemComponent.h"
#include "AbilitySystem/MPAttributeSet.h"

AMPPlayerState::AMPPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMPAbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMPAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AMPPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
