// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/MPGameplayAbility.h"
#include "MPProjectileSpell.generated.h"

class AMPProjectile;

UCLASS()
class UE5_RPG_API UMPProjectileSpell : public UMPGameplayAbility
{
	GENERATED_BODY()

protected:
	/*
	* Actually activate ability, do not call this directly 
	*/
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	/** Projectile to spawn on ActivateAbility */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMPProjectile> ProjectileClass;
};
