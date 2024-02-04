// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/CharacterClassInfoDataAsset.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

FCharacterClassDefaultInfo UCharacterClassInfoDataAsset::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
	return CharacterClassInfoMap.FindChecked(CharacterClass);
}

#if WITH_EDITOR
EDataValidationResult UCharacterClassInfoDataAsset::IsDataValid(FDataValidationContext& Context) const
{
	EDataValidationResult Result = EDataValidationResult::Valid;

	for (const auto& CharacterInfo : CharacterClassInfoMap)
	{
		if (CharacterInfo.Value.PrimaryAttributes == nullptr)
		{
			FString EnumString = StaticEnum<ECharacterClass>()->GetNameStringByValue((int64)CharacterInfo.Key);
			const FText ErrorMsg = FText::FromString(FString::Printf(TEXT("PrimaryAttributes value for [%s] should be valid!"), *EnumString));
			Context.AddError(ErrorMsg);
			Result = EDataValidationResult::Invalid;
		}
	}

	if (SecondaryAttributes == nullptr)
	{
		const FText ErrorMsg = FText::FromString(FString::Printf(TEXT("SecondaryAttributes value should be valid!")));
		Context.AddError(ErrorMsg);
		Result = EDataValidationResult::Invalid;
	}

	if (VitalAttributes == nullptr)
	{
		const FText ErrorMsg = FText::FromString(FString::Printf(TEXT("VitalAttributes value should be valid!")));
		Context.AddError(ErrorMsg);
		Result = EDataValidationResult::Invalid;
	}

	return Result;
}
#endif
