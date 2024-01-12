// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MPUserWidget.h"
#include "UI/WidgetController/MPWidgetController.h"

void UMPUserWidget::SetWidgetController(UMPWidgetController* InWidgetController)
{
	if (!ensureAlwaysMsgf(InWidgetController, TEXT("We always want to set a valid widget controller for MPUserWidget.")))
	{
		return;
	}

	WidgetController = InWidgetController;
	BP_OnSetWidgetController();

	// Blueprints will bind delegates when BP_OnSetWidgetController is triggered. Then we can broadcast delegates.
	WidgetController->BroadcastInitialValues();
}
