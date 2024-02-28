#include "ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MPAttributeSet.h"
#include "MPGameplayTags.h"
#include "AbilitySystem\MPAbilitySystemLibrary.h"
#include <Character\MPCharacterBase.h>
#include <MPAbilityTypes.h>

struct MPDamageStatics
{
	// Target
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);

	// Source
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);

	MPDamageStatics()
	{
		/*
		* DEFINE_ATTRIBUTE_CAPTUREDEF's last param is Snapshotting
		* If true, it captures the Attribute value when the Gameplay Effect Spec is created
		* If false, it captures the Attribute value when the Gameplay Effect is applied
		*/

		// Target attribute info
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMPAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMPAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMPAttributeSet, CriticalHitResistance, Target, false);

		// Souce attribute info
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMPAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMPAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMPAttributeSet, CriticalHitDamage, Source, false);
	}
};

static const MPDamageStatics& DamageStatics()
{
	static MPDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	if (!ensure(SourceASC && TargetASC))
	{
		return;
	}

	AActor* SourceAvatar = SourceASC->GetAvatarActor();
	AActor* TargetAvatar = TargetASC->GetAvatarActor();
	if (!ensure(SourceAvatar && TargetAvatar))
	{
		return;
	}

	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);
	if (!ensure(SourceCombatInterface && TargetCombatInterface))
	{
		return;
	}

	int32 SourceLevel = SourceCombatInterface->GetPlayerLevel();
	int32 TargetLevel = TargetCombatInterface->GetPlayerLevel();

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	// Get Damage Set by Caller Magnitude
	// Damage value is sent with Damage tag by AssignTagSetByCallerMagnitude function. Example is in UMPProjectileSpell::SpawnProjectile
	float Damage = Spec.GetSetByCallerMagnitude(FMPGameplayTags::Get().Damage);

#pragma region BlockChance
	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluateParameters, TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(0.f, TargetBlockChance);
	bool BlockSuccess = TargetBlockChance > FMath::RandRange(0.f, 100.f);
	if (BlockSuccess)
	{
		// if block, halve the damage.
		Damage *= .5f;
	}

	UMPAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, BlockSuccess);
#pragma endregion

#pragma region ArmorPenetration
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(0.f, TargetArmor);

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluateParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(0.f, SourceArmorPenetration);

	const UCharacterClassInfoDataAsset* CharacterClassInfoDataAsset = UMPAbilitySystemLibrary::GetCharacterClassInfoDataAsset(SourceAvatar);
	if (!ensure(CharacterClassInfoDataAsset))
	{
		return;
	}

	// ArmorPenetration ignores a percentage of the target's Armor
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfoDataAsset->DamageCalcCoefficients->FindCurve(FName("ArmorPenetrationCoef"), FString());
	if (!ensure(ArmorPenetrationCurve))
	{
		return;
	}
	const float SourceArmorPenetrationCoef = ArmorPenetrationCurve->Eval(SourceLevel);
	float TargetEffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * SourceArmorPenetrationCoef) / 100.f;
	TargetEffectiveArmor = FMath::Max<float>(0.f, TargetEffectiveArmor);

	// Armor ignores a percentage of incoming damage
	const FRealCurve* EffectiveArmorCurve = CharacterClassInfoDataAsset->DamageCalcCoefficients->FindCurve(FName("EffectiveArmorCoef"), FString());
	if (!ensure(EffectiveArmorCurve))
	{
		return;
	}
	const float TargetEffectiveArmorCoef = EffectiveArmorCurve->Eval(TargetLevel);
	Damage *= (100 - TargetEffectiveArmor * TargetEffectiveArmorCoef) / 100.f;
#pragma endregion

#pragma region CriticalHit
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluateParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(0.f, SourceCriticalHitChance);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluateParameters, SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(0.f, SourceCriticalHitDamage);

	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaluateParameters, TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max<float>(0.f, TargetCriticalHitResistance);

	// CriticalHitResistance reduces source's CritHitChance
	const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfoDataAsset->DamageCalcCoefficients->FindCurve(FName("CriticalHitResistanceCoef"), FString());
	if (!ensure(CriticalHitResistanceCurve))
	{
		return;
	}
	const float TargetCriticalHitResistanceCoef = CriticalHitResistanceCurve->Eval(TargetLevel);
	SourceCriticalHitChance -= TargetCriticalHitResistance * TargetCriticalHitResistanceCoef;

	bool CritHit = SourceCriticalHitChance > FMath::RandRange(0.f, 100.f);
	if (CritHit)
	{
		// if CritHit, double the Damage and add CriticalHitDamage
		Damage = Damage * 2.f + SourceCriticalHitDamage;
	}

	UMPAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, CritHit);
#pragma endregion

	FGameplayModifierEvaluatedData EvaluatedData;
	EvaluatedData.Attribute = UMPAttributeSet::GetIncomingDamageAttribute();
	EvaluatedData.ModifierOp = EGameplayModOp::Additive;
	EvaluatedData.Magnitude = Damage;

	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}