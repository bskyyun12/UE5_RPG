// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/MPInputConfigDataAsset.h"
#include "InputAction.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#if WITH_EDITOR
EDataValidationResult UMPInputConfigDataAsset::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = EDataValidationResult::Valid;
	for (int i = 0; i < AbilityInputActions.Num(); i++)
	{
		if (AbilityInputActions[i].InputAction == nullptr)
		{
			const FText ErrorMsg = FText::FromString(FString::Printf(TEXT("InputAction at index [%i] should be valid!"), i));
			Context.AddError(ErrorMsg);
			Result = EDataValidationResult::Invalid;
		}

		if (AbilityInputActions[i].InputTag.IsValid() == false)
		{
			const FText ErrorMsg = FText::FromString(FString::Printf(TEXT("InputTag at index [%i] should be valid!"), i));
			Context.AddError(ErrorMsg);
			Result = EDataValidationResult::Invalid;
		}
	}

	return Result;
}
#endif
