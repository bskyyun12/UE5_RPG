// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MPHUD.h"
#include "UI/Widget/MPUserWidget.h"

void AMPHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	check(Widget);
	Widget->AddToViewport();
}