// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UAnimMontage;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class UE5_RPG_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetPlayerLevel();

	virtual FVector GetCombatSocketLocation() = 0;	
	virtual TObjectPtr<USkeletalMeshComponent> GetWeapon() = 0;	

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);	

	virtual void OnPossess(ACharacter* TargetCharacter) = 0;

	/*
	* Called in UMPAttributeSet::PostGameplayEffectExecute when the health is below 0
	*/
	virtual void Die() = 0;

	/*
	* BlueprintNativeEvent - It will automatically generate a virtual native version that exists in C++
	* Should be GetHitReactMontage_Implementation when overriding this.
	* Called in blueprint GA_HitReact
	*/ 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();
};
