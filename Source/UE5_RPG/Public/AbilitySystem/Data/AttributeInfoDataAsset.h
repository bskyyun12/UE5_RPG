// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeSet.h"
#include "AttributeInfoDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FMPAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttribute Attribute = FGameplayAttribute();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/*
* UAttributeInfoDataAsset
* Contains data for widgets to receive through its widget controller
* The widget controller broadcasts attribute changes to widgets.
*/
UCLASS()
class UE5_RPG_API UAttributeInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	// Attribute widgets will receive FMPAttributeInfo data through AttributeWidgetController.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMPAttributeInfo> AttributeInfoArray;

#if WITH_EDITOR
	// Valid if Attribute is valid in AttributeInfoArray
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
};
