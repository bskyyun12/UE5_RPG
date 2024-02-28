#pragma once

#include "GameplayEffectTypes.h"
#include "MPAbilityTypes.generated.h"

/*
* Guide to use this custom EffectContext in the project.
* 1. Create a class inherited from UAbilitySystemGlobals. (I named it MPAbilitySystemGlobals)
* 2. Override AllocGameplayEffectContext function and return new FMPGameplayEffectContext()
*		- When calling UAbilitySystemComponent::MakeEffectContext(), you get the EffectContext through AllocGameplayEffectContext
* 3. Go to DefaultGame.ini and add following lines.
*		[/Script/GameplayAbilities.AbilitySystemGlobals]
*		+AbilitySystemGlobalsClassName="/Script/UE5_RPG.MPAbilitySystemGlobals"
*/
USTRUCT(BlueprintType)
struct FMPGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool GetIsBlockedHit() const { return bIsBlockedHit; }
	bool GetIsCriticalHit() const { return bIsCriticalHit; }

	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; }
	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FMPGameplayEffectContext* Duplicate() const
	{
		FMPGameplayEffectContext* NewContext = new FMPGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

protected:

	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;

};

template<>
struct TStructOpsTypeTraits<FMPGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FMPGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};