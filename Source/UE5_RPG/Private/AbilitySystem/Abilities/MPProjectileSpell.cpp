// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MPProjectileSpell.h"
#include "Actor/MPProjectile.h"
#include "Interaction/CombatInterface.h"
#include <AbilitySystemBlueprintLibrary.h>
#include "AbilitySystemComponent.h"

void UMPProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UMPProjectileSpell::SpawnProjectile(const FVector& TargetLocation)
{
	/*
	* If player-controlled
	*	GetOwningActorFromActorInfo() = PlayerState
	*	GetAvatarActorFromActorInfo() = Pawn
	* If AI-controlled
	*	GetOwningActorFromActorInfo() = Pawn
	*	GetAvatarActorFromActorInfo() = Pawn
	*/
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!ensure(AvatarActor))
	{
		return;
	}

	const bool bIsServer = AvatarActor->HasAuthority();
	if (bIsServer == false)
	{
		return;
	}

	if (!ensure(ProjectileClass))
	{
		return;
	}

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(AvatarActor);
	if (!ensure(CombatInterface))
	{
		return;
	}

	// Set SpawnTransform
	const FVector SpawnLocation = CombatInterface->GetCombatSocketLocation();
	FRotator SpawnRotation = (TargetLocation - SpawnLocation).Rotation();
	SpawnRotation.Pitch = 0.f;
	const FTransform SpawnTransform(SpawnRotation.Quaternion(), SpawnLocation);

	// Spawn Projectile
	AMPProjectile* Projectile = GetWorld()->SpawnActorDeferred<AMPProjectile>(
		ProjectileClass,
		SpawnTransform,
		AvatarActor,
		Cast<APawn>(AvatarActor),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	// Set Projectile's DamageEffectSpecHandle using DamageEffectClass before finish spawning
	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(AvatarActor);
	if (!ensure(SourceASC))
	{
		return;
	}
	const FGameplayEffectSpecHandle DamageEffectSpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
	Projectile->DamageEffectSpecHandle = DamageEffectSpecHandle;

	Projectile->FinishSpawning(SpawnTransform);
}
