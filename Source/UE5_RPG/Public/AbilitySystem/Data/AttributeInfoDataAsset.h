// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfoDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FMPAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

UCLASS()
class UE5_RPG_API UAttributeInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FMPAttributeInfo FindAttibuteInforForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMPAttributeInfo> AttributeInformation;
};
