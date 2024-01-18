// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MPProjectileSpell.h"
#include "Actor/MPProjectile.h"
#include "Interaction/CombatInterface.h"

void UMPProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (HasAuthority(&ActivationInfo) == false)
	{
		return;
	}

	if (!ensure(ProjectileClass))
	{
		return;
	}

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!ensure(CombatInterface))
	{
		return;
	}

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(CombatInterface->GetCombatSocketLocation());
	// TODO: Set rotation

	AMPProjectile* Projectile = GetWorld()->SpawnActorDeferred<AMPProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	// TODO: Before finish spawning, give the projectil a gameplay effect spec for causing damage

	Projectile->FinishSpawning(SpawnTransform);
}
