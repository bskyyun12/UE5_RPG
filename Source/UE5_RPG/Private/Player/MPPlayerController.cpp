// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MPPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "Input/MPEnhancedInputComponent.h"
#include "MPGameplayTags.h"
#include "AbilitySystem/MPAbilitySystemComponent.h"
#include <AbilitySystemBlueprintLibrary.h>
#include <Components/SplineComponent.h>
#include <NavigationSystem.h>
#include <NavigationPath.h>

AMPPlayerController::AMPPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AMPPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	TryHighlightingEnemyUnderCursor();

	AutoRun();
}

void AMPPlayerController::AutoRun()
{
	if (!bAutoRunning)
	{
		return;
	}

	if (GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(GetPawn()->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(GetPawn()->GetActorLocation(), ESplineCoordinateSpace::World);
		GetPawn()->AddMovementInput(Direction);

		const float DistToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void AMPPlayerController::TryHighlightingEnemyUnderCursor()
{
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit)
	{
		return;
	}

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (LastActor != ThisActor)
	{
		if (LastActor)
		{
			LastActor->UnHighlightActor();
		}

		if (ThisActor)
		{
			ThisActor->HighlightActor();
		}
	}
}

void AMPPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!ensureAlwaysMsgf(MPContext, TEXT("InputMappingContext is missing in BP_MPPlayerController")))
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (ensure(Subsystem))
	{
		Subsystem->AddMappingContext(MPContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AMPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UMPEnhancedInputComponent* MPInputComponent = Cast<UMPEnhancedInputComponent>(InputComponent);
	if (!ensure(MPInputComponent))
	{
		return;
	}
	MPInputComponent->BindInputActions(InputConfigDataAsset, this, &ThisClass::InputPressed, &ThisClass::InputReleased, &ThisClass::InputHeld);
}

void AMPPlayerController::InputPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());

	if (InputTag == FMPGameplayTags::Get().InputTag_LMB)
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AMPPlayerController::InputReleased(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Blue, *InputTag.ToString());

	/*
	* Targeting, InputTag_LMB => Ability
	* Targeting, !InputTag_LMB => Ability
	* !Targeting, InputTag_LMB => Move
	* !Targeting, !InputTag_LMB => Ability
	*/
	// LMB was meant for moving in this case
	if (!bTargeting && InputTag == FMPGameplayTags::Get().InputTag_LMB)
	{
		if (FollowTime <= ShortPressThreshold && GetPawn())
		{
			const UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, GetPawn()->GetActorLocation(), CachedDestination);
			if (NavPath)
			{
				Spline->ClearSplinePoints();
				for (const FVector& Point : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(Point, ESplineCoordinateSpace::World);
				}
				CachedDestination = NavPath->PathPoints.Last(); // Last path point is our new destination.
				bAutoRunning = true;
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
	else if (GetASC())
	{
		GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}
}

void AMPPlayerController::InputHeld(const FInputActionValue& InputActionValue, FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Green, *InputTag.ToString());

	/*
	* Targeting, InputTag_LMB => Ability
	* Targeting, !InputTag_LMB => Ability
	* !Targeting, InputTag_LMB => Move
	* !Targeting, !InputTag_LMB => Ability
	*/
	// LMB was meant for moving in this case
	if (!bTargeting && InputTag == FMPGameplayTags::Get().InputTag_LMB)
	{

		FollowTime += GetWorld()->GetDeltaSeconds();

		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}

		if (GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - GetPawn()->GetActorLocation()).GetSafeNormal();
			GetPawn()->AddMovementInput(WorldDirection);
		}
	}
	else if (GetASC())
	{
		GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}


	if (InputTag == FMPGameplayTags::Get().InputTag_Move)
	{
		if (ThisActor == nullptr)
		{
			Move(InputActionValue);
		}
	}
}

void AMPPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	APawn* ControlledPawn = GetPawn<APawn>();
	if (ControlledPawn)
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

TObjectPtr<UMPAbilitySystemComponent> AMPPlayerController::GetASC()
{
	if (MPAbilitySystemComponent == nullptr)
	{
		MPAbilitySystemComponent = Cast<UMPAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}

	return MPAbilitySystemComponent;
}
