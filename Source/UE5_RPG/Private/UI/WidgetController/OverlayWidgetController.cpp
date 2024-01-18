// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/MPAttributeSet.h"
#include "AbilitySystem\MPAbilitySystemComponent.h"
#include "MPGameplayTags.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UMPAttributeSet* MPAttributeSet = Cast<UMPAttributeSet>(AttributeSet);
	if (!ensure(MPAttributeSet))
	{
		return;
	}

	OnHealthChanged.Broadcast(MPAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(MPAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(MPAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(MPAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UMPAttributeSet* MPAttributeSet = Cast<UMPAttributeSet>(AttributeSet);
	if (!ensure(MPAttributeSet))
	{
		return;
	}

	UMPAbilitySystemComponent* MPAbilitySystemComponent = Cast<UMPAbilitySystemComponent>(AbilitySystemComponent);
	if (!ensure(MPAbilitySystemComponent))
	{
		return;
	}

	// Health change
	MPAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MPAttributeSet->GetHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
	);

	// MaxHealth change
	MPAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MPAttributeSet->GetMaxHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
	);

	// Mana change
	MPAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MPAttributeSet->GetManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
	);

	// MaxMana change
	MPAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MPAttributeSet->GetMaxManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
	);

	// EffectAssetTags
	MPAbilitySystemComponent->OnReceiveAssetTagsWhenEffectAppliedToSelf.AddLambda([this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				// For example, say that Tag = Message.HealthPotion				
				// FGameplayTag::MatchesTag => "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
				// TODO: Get the gameplay tag from MPGamePlayTags. Need to find a way to get all tags which have "Message"..
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		});
}
