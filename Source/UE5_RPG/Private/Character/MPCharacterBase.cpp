// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MPCharacterBase.h"
#include "AbilitySystemComponent.h"

AMPCharacterBase::AMPCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMPCharacterBase::BeginPlay()
{
	Super::BeginPlay();	
}

void AMPCharacterBase::InitAbilityActorInfo()
{
}

void AMPCharacterBase::InitializePrimaryAttributes() const
{
	if (!ensure(GetAbilitySystemComponent()))
	{
		return;
	}
		
	if (!ensure(DefaultPrimaryAttributes))
	{
		return;
	}

	const FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, EffectContextHandle);
	const FGameplayEffectSpec* EffectSpec = EffectSpecHandle.Data.Get();
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec, GetAbilitySystemComponent());
}

UAbilitySystemComponent* AMPCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
