// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfoDataAsset.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"

EDataValidationResult UAttributeInfoDataAsset::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = EDataValidationResult::Valid;
	for (int i = 0; i < AttributeInfoArray.Num(); i++)
	{
		if (AttributeInfoArray[i].Attribute.IsValid() == false)
		{
			const FText ErrorMsg = FText::FromString(FString::Printf(TEXT("Attribute at index [%i] should be valid!"), i));
			Context.AddError(ErrorMsg);
			Result = EDataValidationResult::Invalid;
		}
	}

	return Result;
}
#endif