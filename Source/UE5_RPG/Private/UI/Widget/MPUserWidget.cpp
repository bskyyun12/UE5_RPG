// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MPUserWidget.h"

void UMPUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
