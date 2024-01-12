// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MPCharacterBase.h"
#include "AbilitySystemComponent.h"

AMPCharacterBase::AMPCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Weapon attachment setup. WeaponHandSocket should be added in the skeleton
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMPCharacterBase::InitAbilityActorInfo()
{
	/*
	* This is meant to be overriden because UAbilitySystemComponent::InitAbilityActorInfo needs to
	* be called depending on if the character is controlled by player or AI. 
	* More details in the definition.
	*/	
}

void AMPCharacterBase::InitializePrimaryAttributes() const
{
	if (!ensure(AbilitySystemComponent))
	{
		return;
	}
		
	if (!ensureMsgf(DefaultPrimaryAttributes, TEXT("DefaultPrimaryAttributes should be set in %s."), *GetName()))
	{
		return;
	}

	// Apply default primary attribute values. 
	const FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, EffectContextHandle);
	const FGameplayEffectSpec* EffectSpec = EffectSpecHandle.Data.Get();
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpec, AbilitySystemComponent);
}

UAbilitySystemComponent* AMPCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
