// Fill out your copyright notice in the Description page of Project Settings.


#include "MPAssetManager.h"
#include "MPGameplayTags.h"

UMPAssetManager& UMPAssetManager::Get()
{
	check(GEngine);
	UMPAssetManager* MPAssetManager = Cast<UMPAssetManager>(GEngine->AssetManager);
	return *MPAssetManager;
}

void UMPAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FMPGameplayTags::InitializeNativeGameplayTags();
}
