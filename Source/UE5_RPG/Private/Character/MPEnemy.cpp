// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MPEnemy.h"
#include "UE5_RPG/UE5_RPG.h"
#include "AbilitySystem/MPAbilitySystemComponent.h"
#include "AbilitySystem/MPAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/MPUserWidget.h"
#include "AbilitySystem/MPAbilitySystemLibrary.h"

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

	HealthBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidgetComp");
	HealthBarWidgetComp->SetupAttachment(GetRootComponent());
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
	InitHealthBar();
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

void AMPEnemy::InitializeDefaultAttributes() const
{
	UMPAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void AMPEnemy::InitHealthBar()
{
	// Set WidgetController
	UMPUserWidget* HealthBarWidget = Cast<UMPUserWidget>(HealthBarWidgetComp->GetUserWidgetObject());
	if (!ensure(HealthBarWidget))
	{
		return;
	}
	HealthBarWidget->SetWidgetController(this);

	// Bind health callbacks
	const UMPAttributeSet* MPAS = Cast<UMPAttributeSet>(AttributeSet);
	if (!ensure(MPAS))
	{
		return;
	}
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MPAS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) {
			OnHealthChanged.Broadcast(Data.NewValue);
		});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MPAS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) {
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});

	// Broadcast initial health values
	OnHealthChanged.Broadcast(MPAS->GetHealth());
	OnMaxHealthChanged.Broadcast(MPAS->GetMaxHealth());
}
