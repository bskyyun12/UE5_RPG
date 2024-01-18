// Fill out your copyright notice in the Description page of Project Settings.


#include "MPGameplayTags.h"
#include "GameplayTagsManager.h"

FMPGameplayTags FMPGameplayTags::GameplayTags;

void FMPGameplayTags::InitializeNativeGameplayTags()
{
	// Primary Attributes Tags
	GameplayTags.Attribute_Primary_Strength
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Strength"), FString("Increases physical damage"));
	GameplayTags.Attribute_Primary_Intelligence
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Intelligence"), FString("Increases magical damage, Mana Regeneration, and Max Mana"));
	GameplayTags.Attribute_Primary_Resilience
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Resilience"), FString("Increases Armor and Armor Penetration"));
	GameplayTags.Attribute_Primary_Vigor
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Vigor"), FString("Increases Max Health and Health Regeneration"));

	// Secondary Attributes Tags
	GameplayTags.Attribute_Secondary_Armor
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.Armor"), FString("Reduced damage taken, improves Block Chance"));
	GameplayTags.Attribute_Secondary_ArmorPenetration
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ArmorPenetration"), FString("Ignores percentage of enemy Armor, increases Crit Hit Chance"));
	GameplayTags.Attribute_Secondary_BlockChance
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.BlockChance"), FString("Chance to cut incoming damage in half"));
	GameplayTags.Attribute_Secondary_CriticalHitChance
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitChance"), FString("Chance to double damage plus critial hit bonus"));
	GameplayTags.Attribute_Secondary_CriticalHitDamage
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitDamage"), FString("Bonus damage added when a critical hit is scored"));
	GameplayTags.Attribute_Secondary_CriticalHitResistance
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitResistance"), FString("Reduces critical hit chance of attacking enemies"));
	GameplayTags.Attribute_Secondary_HealthRegeneration
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.HealthRegeneration"), FString("Amount of Health regenerated every 1 second"));
	GameplayTags.Attribute_Secondary_ManaRegeneration
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ManaRegeneration"), FString("Amount of Mana regenerated every 1 second"));
	GameplayTags.Attribute_Secondary_MaxHealth
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxHealth"), FString("Maximum amount of Health obtainable"));
	GameplayTags.Attribute_Secondary_MaxMana
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxMana"), FString("Maximum amount of Mana obtainable"));

	// Vital Attributes Tags
	GameplayTags.Attribute_Vital_Health
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Vital.Health"), FString(""));
	GameplayTags.Attribute_Vital_Mana
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Vital.Mana"), FString(""));

	// Message Tags
	GameplayTags.Message_HealthCrystal
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthCrystal"), FString(""));
	GameplayTags.Message_HealthPotion
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthPotion"), FString(""));
	GameplayTags.Message_ManaCrystal
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaCrystal"), FString(""));
	GameplayTags.Message_ManaPotion
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaPotion"), FString(""));
	GameplayTags.Message_Gold
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.Gold"), FString(""));

	// Input Tags
	GameplayTags.InputTag_Move
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Move"), FString("Input tag for Move action (WASD)"));
	GameplayTags.InputTag_LMB
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("Input tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("Input tag for Right Mouse Button"));
	GameplayTags.InputTag_1
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), FString("Input tag for 1 Key"));
	GameplayTags.InputTag_2
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), FString("Input tag for 2 Key"));
	GameplayTags.InputTag_3
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), FString("Input tag for 3 Key"));
	GameplayTags.InputTag_4
		= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), FString("Input tag for 4 Key"));
}