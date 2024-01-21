// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PossessSpell.h"
#include "Character/MPEnemy.h"
#include "GameFramework/PawnMovementComponent.h"

void UPossessSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UPossessSpell::Possess(AActor* TargetActor)
{
	AMPCharacterBase* TargetCharacter = Cast<AMPCharacterBase>(TargetActor);
	AMPCharacterBase* AvatarCharacter = Cast<AMPCharacterBase>(GetAvatarActorFromActorInfo());
	ICombatInterface* AvatarCombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!ensure(TargetCharacter) || 
		!ensure(AvatarCharacter) ||
		!ensure(AvatarCombatInterface))
	{
		return;
	}

	const bool bIsServer = AvatarCharacter->HasAuthority();
	if (bIsServer == false)
	{
		return;
	}

	AvatarCombatInterface->OnPossess(TargetCharacter);
}