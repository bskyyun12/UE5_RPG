// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/MPWidgetController.h"

void UMPWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	AttributeSet = WidgetControllerParams.AttributeSet;
}

void UMPWidgetController::BroadcastInitialValues()
{
	
}

void UMPWidgetController::BindCallbacksToDependencies()
{
	
}
