// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MPEnemy.h"
#include "UE5_RPG/UE5_RPG.h"
#include "AbilitySystem/MPAbilitySystemComponent.h"
#include "AbilitySystem/MPAttributeSet.h"

AMPEnemy::AMPEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

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
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMPAttributeSet>("AttributeSet");
}

void AMPEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AMPEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 AMPEnemy::GetPlayerLevel()
{
	return Level;
}

void AMPEnemy::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();
	InitializeDefaultAttributes();
}

void AMPEnemy::InitAbilityActorInfo()
{
	if (!ensure(AbilitySystemComponent))
	{
		return;
	}
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	UMPAbilitySystemComponent* MPAbilitySystemComponent = Cast<UMPAbilitySystemComponent>(AbilitySystemComponent);
	if (!ensure(MPAbilitySystemComponent))
	{
		return;
	}
	MPAbilitySystemComponent->OnInitAbilityActorInfo();
}
