// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "MPInputConfigDataAsset.h"
#include "MPEnhancedInputComponent.generated.h"

UCLASS()
class UE5_RPG_API UMPEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	/*
	* Custom Binding function to include FGameplayTag
	*/
	template<class UserClass, typename FuncType_Pressed, typename FuncType_Released, typename FuncType_Held>
	void BindInputActions(const UMPInputConfigDataAsset* InputConfig, UserClass* Object, FuncType_Pressed PressedFunc, FuncType_Released ReleasedFunc, FuncType_Held HeldFunc);
};

template<class UserClass, typename FuncType_Pressed, typename FuncType_Released, typename FuncType_Held>
inline void UMPEnhancedInputComponent::BindInputActions(const UMPInputConfigDataAsset* InputConfig, UserClass* Object, FuncType_Pressed PressedFunc, FuncType_Released ReleasedFunc, FuncType_Held HeldFunc)
{
	if (!ensure(InputConfig))
	{
		return;
	}

	for (const FMPInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}