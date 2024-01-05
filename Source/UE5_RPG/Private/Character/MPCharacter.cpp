// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MPCharacter.h"
#include "Player/MPPlayerState.h"
#include "Player/MPPlayerController.h"
#include "UI/HUD/MPHUD.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystemComponent.h"

AMPCharacter::AMPCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AMPCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// For the Server
	InitAbilityActorInfo();
}

void AMPCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// For the Client
	InitAbilityActorInfo();
}

void AMPCharacter::InitAbilityActorInfo()
{
	AMPPlayerState* MPPlayerState = GetPlayerState<AMPPlayerState>();
	check(MPPlayerState);
	MPPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MPPlayerState, this);
	AbilitySystemComponent = MPPlayerState->GetAbilitySystemComponent();
	AttributeSet = MPPlayerState->GetAttributeSet();

	AMPPlayerController* MPPlayerController = Cast<AMPPlayerController>(GetController());
	if (MPPlayerController)
	{
		AMPHUD* MPHUD = MPPlayerController->GetHUD<AMPHUD>();
		if (MPHUD)
		{
			MPHUD->InitOverlay(MPPlayerController, MPPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
