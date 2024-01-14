// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include <AbilitySystem\MPAttributeSet.h>
#include "AbilitySystem/Data/AttributeInfoDataAsset.h"
#include "MPGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	//UMPAttributeSet* AS = Cast<UMPAttributeSet>(AttributeSet);
	//if (!ensure(AS))
	//{
	//	return;
	//}

	if (!ensureAlwaysMsgf(AttributeInfoDataAsset, TEXT("AttributeInfoDataAsset is not set in BP_AttributeMenuWidgetController.")))
	{
		return;
	}

	const UMPAttributeSet* AS = AbilitySystemComponent->GetSet<UMPAttributeSet>();
	if (!ensure(AS))
	{
		return;
	}

	FMPAttributeInfo Info = AttributeInfoDataAsset->FindAttibuteInforForTag(FMPGameplayTags::Get().Attribute_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{

}
