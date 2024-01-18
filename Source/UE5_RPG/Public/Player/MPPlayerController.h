// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "MPPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UMPInputConfigDataAsset;
class UMPAbilitySystemComponent;
class USplineComponent;

UCLASS()
class UE5_RPG_API AMPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMPPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	IEnemyInterface* LastActor; // Used to unhighlight actor
	IEnemyInterface* ThisActor; // Used to highlight actor
	FHitResult CursorHit;

	/** Checks if there is an actor with IEnemyInterface under the cursor. If so, highlight it.	*/
	void TryHighlightingEnemyUnderCursor();

	UPROPERTY()
	TObjectPtr<UMPAbilitySystemComponent> MPAbilitySystemComponent;

	TObjectPtr<UMPAbilitySystemComponent> GetASC();

		
	//~ Begin Input related
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> MPContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UMPInputConfigDataAsset> InputConfigDataAsset;

	void InputPressed(FGameplayTag InputTag);
	void InputReleased(FGameplayTag InputTag);
	void InputHeld(const FInputActionValue& InputActionValue, FGameplayTag InputTag);
	
	FVector CachedDestination = FVector();
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	float AutoRunAcceptanceRadius = 50.f;
	bool bTargeting = false;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;
	void Move(const FInputActionValue& InputActionValue);
	void AutoRun();
	//~ End Input related
};
