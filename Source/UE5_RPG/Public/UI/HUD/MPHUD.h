// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MPHUD.generated.h"

class UMPUserWidget;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;
class UOverlayWidget;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class UE5_RPG_API AMPHUD : public AHUD
{
	GENERATED_BODY()

public:
	// if OverlayWidgetController is nullptr, create one with given OverlayWidgetControllerClass
	UOverlayWidgetController* CreateOrGetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	UAttributeMenuWidgetController* CreateOrGetAttributeMenuWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	void CreateAndInitOverlayWidget(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
protected:

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMPUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
