// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendTargetData();
	}
	else
	{
		/*
		* There are two cases here
		*	1. Server calls Activate(), Then Server receives TargetData
		*		-> Since FAbilityTargetDataSetDelegate is already bound to our function in Activate, when the server receives the Targetdata, trigger FAbilityTargetDataSetDelegate, and it will just broadcast our delegate. No issue.
		*	2. Server receives TargetData, Then Server calls Activate()
		*		-> Here FAbilityTargetDataSetDelegate is already triggered before we bind it to our function. The broadcast already happened before we bound to it.
		*		-> In this case, we can call CallReplicatedTargetDataDelegatesIfSet. It will force the broadcast of FAbilityTargetDataSetDelegate again.
		*/
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		
		// Bind the TargetData delegate
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		
		// Check if the TargetData delegate is called. If not, wait for it to be called.
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			// Telling that we are still waiting for playerdata.
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderMouse::SendTargetData()
{
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());

	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	if (!ensure(PC))
	{
		return;
	}

	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();

	FHitResult HitResult;
	PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	Data->HitResult = HitResult;

	FGameplayAbilityTargetDataHandle TargetDataHandle;
	TargetDataHandle.Add(Data);
	
	/** Sends TargetData to the server */
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		TargetDataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidDataHandle.Broadcast(TargetDataHandle);
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidDataHandle.Broadcast(TargetDataHandle);
	}
}
