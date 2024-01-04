// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MPCharacterBase.h"

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

UAbilitySystemComponent* AMPCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
