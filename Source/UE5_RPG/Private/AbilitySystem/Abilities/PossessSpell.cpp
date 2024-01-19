// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PossessSpell.h"
#include "Character/MPEnemy.h"
#include "GameFramework/PawnMovementComponent.h"

void UPossessSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (HasAuthority(&ActivationInfo) == false)
	{
		return;
	}

	ICombatInterface* AvatarCombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!ensure(AvatarCombatInterface))
	{
		return;
	}
	
	// TODO: Don't spawn it. Get target class
	AMPCharacterBase* Character = Cast<AMPCharacterBase>(GetAvatarActorFromActorInfo());
	AMPEnemy* Enemy = GetWorld()->SpawnActor<AMPEnemy>(EnemyClassToPossess);	
	ICombatInterface* EnemyCombatInterface = Cast<ICombatInterface>(Enemy);
	if (!ensure(EnemyCombatInterface))
	{
		return;
	}

	Character->GetMesh()->SetSkeletalMesh(Enemy->GetMesh()->GetSkeletalMeshAsset());
	Character->GetMesh()->SetAnimClass(Enemy->GetMesh()->GetAnimClass());
	AvatarCombatInterface->GetWeapon()->SetSkeletalMesh(EnemyCombatInterface->GetWeapon()->GetSkeletalMeshAsset());
	// TODO: Set movement speed
	// TODO: Remove Character's abilities and Take Enemy's abilities
}
