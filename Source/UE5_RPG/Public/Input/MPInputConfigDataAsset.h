// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "MPInputConfigDataAsset.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FMPInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

UCLASS()
class UE5_RPG_API UMPInputConfigDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	/*
	* Mapping UInputAction and FGameplayTag(InputTag). 
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMPInputAction> AbilityInputActions;

#if WITH_EDITOR
	// Valid if InputAction and InputTag are valid in AbilityInputActions
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif

};
