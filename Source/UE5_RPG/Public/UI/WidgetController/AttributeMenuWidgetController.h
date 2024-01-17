// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/MPWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

struct FMPAttributeInfo;
class UAttributeInfoDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoDelegate, const FMPAttributeInfo&, Info);

UCLASS(BlueprintType, Blueprintable)
class UE5_RPG_API UAttributeMenuWidgetController : public UMPWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
		
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoDelegate AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAttributeInfoDataAsset> AttributeInfoDataAsset;

private:
	void BroadcastAttributeInfo(FMPAttributeInfo& Info) const;
};
