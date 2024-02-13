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
class UDamageTextComponent;

UCLASS()
class UE5_RPG_API AMPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMPPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

	// Damage Text
	UFUNCTION(Client, Reliable)
	void Client_ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter);

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
		
#pragma region Input
	UPROPERTY(EditAnywhere, Category = "MP|Input")
	TObjectPtr<UInputMappingContext> MPContext;

	UPROPERTY(EditDefaultsOnly, Category = "MP|Input")
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
#pragma endregion

	// Damage Text
	UPROPERTY(EditDefaultsOnly, Category = "MP|UI")
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
