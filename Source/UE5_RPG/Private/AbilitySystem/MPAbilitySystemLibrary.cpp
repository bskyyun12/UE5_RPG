// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MPAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HUD/MPHUD.h"
#include "Player/MPPlayerState.h"
#include "UI/WidgetController/MPWidgetController.h"
#include "Game/MPGameModeBase.h"
#include "AbilitySystem/Data/CharacterClassInfoDataAsset.h"
#include "AbilitySystemComponent.h"
#include <MPAbilityTypes.h>

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

	FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	return MPHUD->CreateOrGetAttributeMenuWidgetController(WidgetControllerParams);
}

void UMPAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	if (!ensure(ASC))
	{
		return;
	}

	UCharacterClassInfoDataAsset* CharacterClassInfoDataAsset = GetCharacterClassInfoDataAsset(WorldContextObject);
	if (!ensure(CharacterClassInfoDataAsset))
	{
		return;
	}

	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfoDataAsset->GetClassDefaultInfo(CharacterClass);
	
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(ASC->GetAvatarActor());

	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfoDataAsset->SecondaryAttributes, Level, ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfoDataAsset->VitalAttributes, Level, ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UMPAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	if (!ensure(ASC))
	{
		return;
	}

	const UCharacterClassInfoDataAsset* CharacterClassInfoDataAsset = GetCharacterClassInfoDataAsset(WorldContextObject);
	if (!ensure(CharacterClassInfoDataAsset))
	{
		return;
	}

	for (auto AbilityClass: CharacterClassInfoDataAsset->CommonAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfoDataAsset* UMPAbilitySystemLibrary::GetCharacterClassInfoDataAsset(const UObject* WorldContextObject)
{
	const AMPGameModeBase* MPGM = Cast<AMPGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (MPGM == nullptr)
	{
		return nullptr;
	}

	return MPGM->CharacterInfoDataAsset;
}

bool UMPAbilitySystemLibrary::GetIsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FMPGameplayEffectContext* MPContext = static_cast<const FMPGameplayEffectContext*>(EffectContextHandle.Get());
	return MPContext ? MPContext->GetIsBlockedHit() : false;
}

bool UMPAbilitySystemLibrary::GetIsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FMPGameplayEffectContext* MPContext = static_cast<const FMPGameplayEffectContext*>(EffectContextHandle.Get());
	return MPContext ? MPContext->GetIsCriticalHit() : false;
}

void UMPAbilitySystemLibrary::SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool InIsBlockedHit)
{
	//FMPGameplayEffectContext* MPContext = StaticCast<FMPGameplayEffectContext*>(EffectContextHandle.Get());
	FMPGameplayEffectContext* MPContext = static_cast<FMPGameplayEffectContext*>(EffectContextHandle.Get());
	if (MPContext)
	{
		MPContext->SetIsBlockedHit(InIsBlockedHit);
	}
}

void UMPAbilitySystemLibrary::SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool InIsCriticalHit)
{
	FMPGameplayEffectContext* MPContext = static_cast<FMPGameplayEffectContext*>(EffectContextHandle.Get());
	if (MPContext)
	{
		MPContext->SetIsCriticalHit(InIsCriticalHit);
	}
}
