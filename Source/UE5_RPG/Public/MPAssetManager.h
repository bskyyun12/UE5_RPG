// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MPAssetManager.generated.h"

/**
 *
 */
UCLASS()
class UE5_RPG_API UMPAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UMPAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
