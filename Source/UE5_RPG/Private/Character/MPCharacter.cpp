// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MPCharacter.h"
#include "AbilitySystem\MPAbilitySystemComponent.h"
#include "Player/MPPlayerState.h"
#include "Player/MPPlayerController.h"
#include "UI/HUD/MPHUD.h"

#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <AbilitySystemComponent.h>

AMPCharacter::AMPCharacter()
{
	// Begin A typical top-down setup
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 750.f;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComponent->SetupAttachment(SpringArmComponent);
	// End A typical top-down setup
}

int32 AMPCharacter::GetPlayerLevel()
{
	const AMPPlayerState* MPPlayerState = GetPlayerState<AMPPlayerState>();
	if (!ensure(MPPlayerState))
	{
		return 0;
	}
	return MPPlayerState->GetPlayerLevel();
}

//Only called on the server
void AMPCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server InitAbilityActorInfo
	InitAbilityActorInfo();

	// Initializing attributes on the server. Clients will get replicated values.
	InitializeDefaultAttributes();
}

void AMPCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Client InitAbilityActorInfo
	InitAbilityActorInfo();
}

void AMPCharacter::InitAbilityActorInfo()
{
	AMPPlayerState* MPPlayerState = GetPlayerState<AMPPlayerState>();
	if (!ensure(MPPlayerState))
	{
		return;
	}

	AbilitySystemComponent = MPPlayerState->GetAbilitySystemComponent();
	if (!ensure(AbilitySystemComponent))
	{
		return;
	}
	AbilitySystemComponent->InitAbilityActorInfo(MPPlayerState, this);

	UMPAbilitySystemComponent* MPAbilitySystemComponent = Cast<UMPAbilitySystemComponent>(AbilitySystemComponent);
	if (!ensure(MPAbilitySystemComponent))
	{
		return;
	}
	MPAbilitySystemComponent->BindEffectAppliedToSelfEvent();

	AttributeSet = MPPlayerState->GetAttributeSet();
	if (!ensure(AttributeSet))
	{
		return;
	}

	// HUD setup - Initialize Overlay widget
	AMPPlayerController* MPPlayerController = Cast<AMPPlayerController>(GetController());
	if (ensureAlways(MPPlayerController))
	{
		AMPHUD* MPHUD = MPPlayerController->GetHUD<AMPHUD>();
		if (ensureAlways(MPHUD))
		{
			MPHUD->CreateAndInitOverlayWidget(MPPlayerController, MPPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}