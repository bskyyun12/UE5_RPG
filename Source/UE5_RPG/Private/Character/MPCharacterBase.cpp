// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MPCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MPAbilitySystemComponent.h"

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

void AMPCharacterBase::InitializeDefaultAttributes() const
{
	// Apply default Primary attribute values.
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);

	// Apply default Secondary attribute values.
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);

	// Apply default Vital attribute values.
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AMPCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, const float& Level) const
{	
	if (!ensure(AbilitySystemComponent))
	{
		return;
	}
		
	if (!ensure(EffectClass))
	{
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, Level, EffectContextHandle);
	const FGameplayEffectSpec EffectSpec = *EffectSpecHandle.Data.Get();
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(EffectSpec, AbilitySystemComponent);
}

void AMPCharacterBase::AddStartAbilities()
{
	if (!HasAuthority())
	{
		return;
	}

	UMPAbilitySystemComponent* ASC = Cast<UMPAbilitySystemComponent>(AbilitySystemComponent);
	if (!ensure(ASC))
	{
		return;
	}

	ASC->AddAbilities(StartAbilities);
}

UAbilitySystemComponent* AMPCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
