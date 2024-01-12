// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MPPlayerState.h"
#include "AbilitySystem/MPAbilitySystemComponent.h"
#include "AbilitySystem/MPAttributeSet.h"

AMPPlayerState::AMPPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMPAbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);

	/*
	* EGameplayEffectReplicationMode::Full = Gameplay Effects are replicated to all clients.
	* Use case: Singleplayer
	* 
	* EGameplayEffectReplicationMode::Mixed = Gameplay Effects are replicated to the owning client only.
	* Gameplay Cues and Gameplay Tags are replicated to all clients.
	* Use case: Multiplayer, Player controlled
	* 
	* EGameplayEffectReplicationMode::Minimal = Gameplay Effects are "NOT" replicated.
	* Gameplay Cues and Gameplay Tags are replicated to all clients.
	* Use case: Multiplayer, AI controlled
	*/
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMPAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AMPPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
