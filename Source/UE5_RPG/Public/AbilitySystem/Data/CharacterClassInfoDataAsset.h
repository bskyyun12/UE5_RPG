// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfoDataAsset.generated.h"

class UGameplayEffect;
class UGameplayAbility;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Elementalist,
	Warrior,
	Ranger
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{	
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;
};

UCLASS()
class UE5_RPG_API UCharacterClassInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);

	UPROPERTY(EditDefaultsOnly, Category = "MP|Character Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInfoMap;

	UPROPERTY(EditDefaultsOnly, Category = "MP|Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category = "MP|Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category = "MP|Common Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;
		
	UPROPERTY(EditDefaultsOnly, Category = "MP|Common Class Defaults|Damage")
	TObjectPtr<UCurveTable> DamageCalcCoefficients;

#if WITH_EDITOR
	// Valid if Attribute is valid in AttributeInfoArray
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
};
