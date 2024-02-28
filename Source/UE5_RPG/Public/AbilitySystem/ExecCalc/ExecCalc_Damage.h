// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 * Can capture multiple Attributes
 * Can change more than one Attribute
 *		- This makes it more powerful than MMC, which can only change a single Attribute
 * Can have programmer logic
 * 
 * Does NOT support prediction
 * Can Only be used for Instant or Periodic Gameplay Effects (No Infinite nor Duration)
 * Capturing doesn't run PreAttributeChange. Any clamping done there must be done again here
 * Only run on the Server from Gameplay Abilities with Local Predicted, Server Initiated, and Server Only Net Execution Policies
 */
UCLASS()
class UE5_RPG_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UExecCalc_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
