// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MPCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
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
	
	//~ Begin IEnemyInterface
	virtual int32 GetPlayerLevel() override;
	//~ End IEnemyInterface
	
	UPROPERTY(BlueprintAssignable, Category = "MPEnemy|Attribute")
	FOnAttributeChangedDelegate OnHealthChanged;
		
	UPROPERTY(BlueprintAssignable, Category = "MPEnemy|Attribute")
	FOnAttributeChangedDelegate OnMaxHealthChanged;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere, Category = "MPEnemy|Combat")
	TObjectPtr<UWidgetComponent> HealthBarWidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MPEnemy|Class Defaults")
	int32 Level = 1;

private:
	void InitHealthBar();
};
