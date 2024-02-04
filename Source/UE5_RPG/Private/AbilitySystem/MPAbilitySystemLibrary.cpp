// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MPAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/MPHUD.h"
#include "Player/MPPlayerState.h"
#include "UI/WidgetController/MPWidgetController.h"
#include "Game/MPGameModeBase.h"
#include "AbilitySystem/Data/CharacterClassInfoDataAsset.h"
#include "AbilitySystemComponent.h"

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

void UMPAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	if (!ensure(ASC))
	{
		return;
	}

	const AMPGameModeBase* MPGM = Cast<AMPGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!MPGM)
	{
		return;
	}

	UCharacterClassInfoDataAsset* CharacterClassInfoDataAsset = MPGM->CharacterInfoDataAsset;
	if (!ensure(CharacterClassInfoDataAsset))
	{
		return;
	}

	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfoDataAsset->GetClassDefaultInfo(CharacterClass);
	
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(ASC->GetAvatarActor());

	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfoDataAsset->SecondaryAttributes, Level, ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfoDataAsset->VitalAttributes, Level, ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}
