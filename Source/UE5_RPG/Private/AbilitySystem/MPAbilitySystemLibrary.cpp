// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MPAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/MPHUD.h"
#include "Player/MPPlayerState.h"
#include "UI/WidgetController/MPWidgetController.h"

UOverlayWidgetController* UMPAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!ensure(PC))
	{
		return nullptr;
	}

	AMPHUD* MPHUD = Cast<AMPHUD>(PC->GetHUD());
	if (!ensure(MPHUD))
	{
		return nullptr;
	}

	AMPPlayerState* PS = PC->GetPlayerState<AMPPlayerState>();
	if (!ensure(PS))
	{
		return nullptr;
	}

	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	ensure(ASC);

	UAttributeSet* AS = PS->GetAttributeSet();
	ensure(AS);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	return MPHUD->CreateOrGetOverlayWidgetController(WidgetControllerParams);
}

UAttributeMenuWidgetController* UMPAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (!ensure(PC))
	{
		return nullptr;
	}

	AMPHUD* MPHUD = Cast<AMPHUD>(PC->GetHUD());
	if (!ensure(MPHUD))
	{
		return nullptr;
	}

	AMPPlayerState* PS = PC->GetPlayerState<AMPPlayerState>();
	if (!ensure(PS))
	{
		return nullptr;
	}

	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	ensure(ASC);

	UAttributeSet* AS = PS->GetAttributeSet();
	ensure(AS);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	return MPHUD->CreateOrGetAttributeMenuWidgetController(WidgetControllerParams);
}