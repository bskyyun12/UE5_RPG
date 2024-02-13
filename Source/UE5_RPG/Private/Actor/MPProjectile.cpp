// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MPProjectile.h"
#include "UE5_RPG\UE5_RPG.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"

AMPProjectile::AMPProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovementComp->InitialSpeed = 550.f;
	ProjectileMovementComp->MaxSpeed = 550.f;
	ProjectileMovementComp->ProjectileGravityScale = 0.f;
}

void AMPProjectile::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
	FlyingAudioComp = UGameplayStatics::SpawnSoundAttached(FlyingSound, RootComponent);
	FlyingAudioComp->bStopWhenOwnerDestroyed = true;
	SetLifeSpan(LifeSpan);
}

void AMPProjectile::Destroyed()
{
	// Clients play effects
	if (!HasAuthority())
	{
		PlayHitEffect();
	}

	Super::Destroyed();
}

void AMPProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Server play effects and Destroy. Clients will play effects in Destroyed()
	if (HasAuthority())
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
		if (TargetASC && DamageEffectSpecHandle.IsValid())
		{
			FGameplayEffectSpec* DamageEffectSpec = DamageEffectSpecHandle.Data.Get();
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpec);
		}

		PlayHitEffect();
		Destroy();
	}
}

void AMPProjectile::PlayHitEffect()
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
}

