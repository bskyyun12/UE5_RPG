// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MPCharacterBase.generated.h"

UCLASS(Abstract)
class UE5_RPG_API AMPCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMPCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
