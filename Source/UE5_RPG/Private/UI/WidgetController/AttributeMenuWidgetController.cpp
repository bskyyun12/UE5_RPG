// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include <AbilitySystem\MPAttributeSet.h>
#include "AbilitySystem/Data/AttributeInfoDataAsset.h"
#include "MPGameplayTags.h"
#include "GameplayTagsManager.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	if (!ensureAlwaysMsgf(AttributeInfoDataAsset, TEXT("AttributeInfoDataAsset is not set in BP_AttributeMenuWidgetController.")))
	{
		return;
	}

	for (FMPAttributeInfo& Info : AttributeInfoDataAsset->AttributeInfoArray)
	{
		BroadcastAttributeInfo(Info);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	if (!ensureAlwaysMsgf(AttributeInfoDataAsset, TEXT("AttributeInfoDataAsset is not set in BP_AttributeMenuWidgetController.")))
	{
		return;
	}

	for (FMPAttributeInfo& Info : AttributeInfoDataAsset->AttributeInfoArray)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Info.Attribute).AddLambda(
			[this, &Info](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Info);
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(FMPAttributeInfo& Info) const
{
	Info.AttributeValue = Info.Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
