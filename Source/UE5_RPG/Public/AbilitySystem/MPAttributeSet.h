// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MPAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	UPROPERTY()
	FGameplayEffectContextHandle EffectContextHandle = FGameplayEffectContextHandle();

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> SourceAvatarActor = nullptr;
	UPROPERTY()
	TObjectPtr<AController> SourceController = nullptr;
	UPROPERTY()
	TObjectPtr<ACharacter> SourceCharacter = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> TargetAvatarActor = nullptr;
	UPROPERTY()
	TObjectPtr<AController> TargetController = nullptr;
	UPROPERTY()
	TObjectPtr<ACharacter> TargetCharacter = nullptr;
};

UCLASS()
class UE5_RPG_API UMPAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UMPAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	/*
	*	Primary Attributes
	* 
	*	Strength: Increases physical damage
	*	Intelligence: Increases magical damage, Mana Regeneration, and Max Mana
	*	Resilience: Increases Armor and Armor Penetration
	*	Vigor: Increases Max Health and Health Regeneration
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(ThisClass, Strength);
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(ThisClass, Intelligence);
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(ThisClass, Resilience);
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(ThisClass, Vigor);
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	/*
	*	Secondary Attributes
	* 
	*	Armor: Reduces damange taken, improves Block Chance
	*			- Influenced by Resilience
	*	ArmorPenetration: Ignores percentage of enemy Armor, increases Crit Hit Chance
	*			- Influenced by Resilience
	*	BlockChance: Chance to cut incoming damage in half
	*			- Influenced by Armor
	*	CriticalHitChance: Chance to double damage plus critial hit bonus
	*			- Influenced by Armor Penetration
	*	CriticalHitDamage: Bonus damage added when a critical hit is scored
	*			- Influenced by Armor Penetration
	*	CriticalHitResistance: Reduces critical hit chance of attacking enemies
	*			- Influenced by Armor
	*	HealthRegeneration: Amount of Health regenerated every 1 second
	*			- Influenced by Vigor
	*	ManaRegeneration: Amount of Mana regenerated every 1 second
	*			- Influenced by Intelligence
	*	MaxHealth: Maximum amount of Health obtainable
	*			- Influenced by Vigor
	*	MaxMana: Maximum amount of Mana obtainable
	*			- Influenced by Intelligence
	*/		
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(ThisClass, Armor);
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(ThisClass, ArmorPenetration);
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(ThisClass, BlockChance);
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitChance);
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitDamage);
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(ThisClass, CriticalHitResistance);
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(ThisClass, HealthRegeneration);
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(ThisClass, ManaRegeneration);
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMana);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	/*
	*	Vital Attributes
	*	Health:
	*	Mana:
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(ThisClass, Health);
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(ThisClass, Mana);
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;


private:
	void SetEffectProperties(const struct FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
