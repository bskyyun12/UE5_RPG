// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/MPCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "MPEnemy.generated.h"

/**
 *
 */
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


protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character defaults")
	int32 Level = 1;
};
