// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MPEffectActor.h"
#include "Components/SphereComponent.h"

#include <AbilitySystemInterface.h> //IAbilitySystemInterface
#include <AbilitySystemComponent.h> 
#include "AbilitySystem\MPAttributeSet.h"

AMPEffectActor::AMPEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);
}

void AMPEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OtherActor);
	if (AbilitySystemInterface)
	{
		const UMPAttributeSet* MPAttributeSet = Cast<UMPAttributeSet>(AbilitySystemInterface->GetAbilitySystemComponent()->GetAttributeSet(UMPAttributeSet::StaticClass()));
		
		UMPAttributeSet* MutableAuraAttributeSet = const_cast<UMPAttributeSet*>(MPAttributeSet);
		MutableAuraAttributeSet->SetHealth(MPAttributeSet->GetHealth() + 25.f);
		MutableAuraAttributeSet->SetMana(MPAttributeSet->GetMana() - 25.f);
		Destroy();
	}
}

void AMPEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AMPEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndOverlap);
}

