// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfoDataAsset.h"

FMPAttributeInfo UAttributeInfoDataAsset::FindAttibuteInforForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FMPAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find info for AttributeTag [%s] on AttributeInfo [%s]"), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FMPAttributeInfo();
}