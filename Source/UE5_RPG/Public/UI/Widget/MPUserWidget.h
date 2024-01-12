// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MPUserWidget.generated.h"

class UMPWidgetController;

/*
* All widgets in this project will be created from this class.
*/
UCLASS()
class UE5_RPG_API UMPUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UMPWidgetController* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMPWidgetController> WidgetController;

protected:
	// Called when setting a "valid" WidgetController.
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnSetWidgetController"))
	void BP_OnSetWidgetController();
};
