// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/MPAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UMPAttributeSet* MPAttributeSet = CastChecked<UMPAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(MPAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(MPAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(MPAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(MPAttributeSet->GetMaxMana());
}
