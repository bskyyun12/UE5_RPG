// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "GameFramework/Character.h"
#include "MPCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
struct FGameplayEffectSpec;

UCLASS(Abstract)
class UE5_RPG_API AMPCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AMPCharacterBase();

	// Inherited via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Creating getter for AttributeSet is convenient
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY(EditAnywhere, Category = "MPCharacter|Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "MPCharacter|Combat")
	FName WeaponTipSocketName = FName("TipSocket");

	virtual FVector GetCombatSocketLocation() override;

	// AbilitySystemComponent is initially set in PlayerState(if Player controlled character) or in child classes(if AI controlled character)
	UPROPERTY(VisibleAnywhere, Category = "MPCharacter|GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	// AttributeSet is initially set in PlayerState(if Player controlled character) or in child classes(if AI controlled character)
	UPROPERTY(VisibleAnywhere, Category = "MPCharacter|GAS")
	TObjectPtr<UAttributeSet> AttributeSet;

	/*
	* Each child will override this function and call UAbilitySystemComponent::InitAbilityActorInfo
	* This must be called after possession.
	* 1. Player controlled character, ASC lives on the Pawn
	*		Server - PossessedBy
	*		Client - AcknowledgePossession
	* 2. Player controlled character, ASC lives on the PlayerState
	*		Server - PossessedBy
	*		Client - OnRep_PlayerState
	* 3. AI controlled character
	*		Server - BeginPlay
	*		Client - BeginPlay	*
	* In this project, we use 2 and 3
	*/
	virtual void InitAbilityActorInfo();

	/*
	* There are 2 ways to set default values for attributes
	* 1. Using DefaultStartingData in UAbilitySystemComponent. You need to create a matching DataTable(FAttributeMetaData) and UAttributeSet::InitFromMetaDataTable will be called.
	* 2. Using GameplayEffect (Preferred way)
	* In this project, I will use the second way.
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MPCharacter|GAS|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MPCharacter|GAS|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "MPCharacter|GAS|Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	// Applying GameplayEffect using DefaultPrimaryAttributes, DefaultSecondaryAttributes
	void InitializeDefaultAttributes() const;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass, const float& Level) const;

protected:
	void AddStartAbilities();

private:
	UPROPERTY(EditAnywhere, Category = "MPCharacter|GAS|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartAbilities;
};
