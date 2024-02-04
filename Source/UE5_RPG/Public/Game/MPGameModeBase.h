// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MPGameModeBase.generated.h"

class UCharacterClassInfoDataAsset;

UCLASS()
class UE5_RPG_API AMPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfoDataAsset> CharacterInfoDataAsset;
};
