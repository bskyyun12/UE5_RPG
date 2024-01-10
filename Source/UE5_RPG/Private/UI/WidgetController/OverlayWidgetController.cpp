// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/MPAttributeSet.h"
#include "AbilitySystem\MPAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UMPAttributeSet* MPAttributeSet = CastChecked<UMPAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(MPAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(MPAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(MPAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(MPAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UMPAttributeSet* MPAttributeSet = CastChecked<UMPAttributeSet>(AttributeSet);

	check(AbilitySystemComponent);

	UMPAbilitySystemComponent* MPAbilitySystemComponent = Cast<UMPAbilitySystemComponent>(AbilitySystemComponent);
	check(MPAbilitySystemComponent);

	// Health change
	FOnGameplayAttributeValueChange& HealthChanged = MPAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MPAttributeSet->GetHealthAttribute());
	HealthChanged.AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	// MaxHealth change
	FOnGameplayAttributeValueChange& MaxHealthChanged = MPAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MPAttributeSet->GetMaxHealthAttribute());
	MaxHealthChanged.AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	// Mana change
	FOnGameplayAttributeValueChange& ManaChanged = MPAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MPAttributeSet->GetManaAttribute());
	ManaChanged.AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	// MaxMana change
	FOnGameplayAttributeValueChange& MaxManaChanged = MPAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MPAttributeSet->GetMaxManaAttribute());
	MaxManaChanged.AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	// EffectAssetTags
	MPAbilitySystemComponent->EffectAssetTags.AddLambda([this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				// For example, say that Tag = Message.HealthPotion				
				// FGameplayTag::MatchesTag => "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		});
}