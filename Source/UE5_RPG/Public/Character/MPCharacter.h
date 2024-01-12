// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MPCharacterBase.h"
#include "MPCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AMPPlayerState;

UCLASS()
class UE5_RPG_API AMPCharacter : public AMPCharacterBase
{
	GENERATED_BODY()

public:
	AMPCharacter();

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

protected:
	/** 
	 * Called when this Pawn is possessed. Only called on the server (or in standalone).
	 * @param NewController The controller possessing this pawn
	 */
	virtual void PossessedBy(AController* NewController) override;

	/** If Pawn is possessed by a player, points to its Player State.  Needed for network play as controllers are not replicated to clients. */
	virtual void OnRep_PlayerState() override;
	
	virtual void InitAbilityActorInfo() override;
};
