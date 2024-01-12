// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MPHUD.h"
#include "UI/Widget/MPUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AMPHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		if (!ensureAlwaysMsgf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is nullptr. Please fill out BP_MPHUD")))
		{
			return nullptr;
		}

		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
	}

	return OverlayWidgetController;
}

void AMPHUD::CreateAndInitOverlayWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	if (!ensureAlwaysMsgf(OverlayWidgetClass, TEXT("OverlayWidgetClass is nullptr. Please fill out BP_MPHUD")))
	{
		return;
	}

	UMPUserWidget* MPOverlayWidget = CreateWidget<UMPUserWidget>(GetWorld(), OverlayWidgetClass);
	if (!ensure(MPOverlayWidget))
	{
		return;
	}

	// Set widget controller
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	MPOverlayWidget->SetWidgetController(WidgetController);

	MPOverlayWidget->AddToViewport();
}