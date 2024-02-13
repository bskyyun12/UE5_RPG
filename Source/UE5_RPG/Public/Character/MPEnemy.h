// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MPCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem\Data\CharacterClassInfoDataAsset.h"
#include "MPEnemy.generated.h"

class UWidgetComponent;

UCLASS()
class UE5_RPG_API AMPEnemy : public AMPCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AMPEnemy();

	//~ Begin IEnemyInterface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//~ End IEnemyInterface
	
	//~ Begin ICombatInterface
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	//~ End ICombatInterface
	
	UPROPERTY(BlueprintAssignable, Category = "MPEnemy|Attribute")
	FOnAttributeChangedDelegate OnHealthChanged;
		
	UPROPERTY(BlueprintAssignable, Category = "MPEnemy|Attribute")
	FOnAttributeChangedDelegate OnMaxHealthChanged;

	UFUNCTION()
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	UPROPERTY(BlueprintReadOnly, Category = "MPEnemy|Combat")
	bool bHitReacting;
	
	UPROPERTY(BlueprintReadOnly, Category = "MPEnemy|Combat")
	float BaseWalkSpeed = 250.f;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MPEnemy|Combat")
	float LifeSpan = 5.f;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;
	
	UPROPERTY(EditAnywhere, Category = "MPEnemy|Combat")
	TObjectPtr<UWidgetComponent> HealthBarWidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MPEnemy|Class Defaults")
	int32 Level = 1;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MPEnemy|Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

private:
	void InitHealthBar();
};
