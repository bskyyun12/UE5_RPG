// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/MPProjectileSpell.h"
#include "Actor/MPProjectile.h"
#include "Interaction/CombatInterface.h"

void UMPProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!ensure(ProjectileClass))
	{
		return;
	}

	if (HasAuthority(&ActivationInfo) == false)
	{
		return;
	}

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		AActor* OwnerActor = GetOwningActorFromActorInfo();

		APawn* Instigator = Cast<APawn>(OwnerActor);

		AMPProjectile* Projectile = GetWorld()->SpawnActorDeferred<AMPProjectile>(
			ProjectileClass,
			SpawnTransform,
			OwnerActor,
			Instigator,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		// TODO: Before finish spawning, give the projectil a gameplay effect spec for causing damage.

		Projectile->FinishSpawning(SpawnTransform);

	}

}
