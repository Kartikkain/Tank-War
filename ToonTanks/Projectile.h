// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Combat",meta = (AllowPrivateAccess = "true"))
UStaticMeshComponent* ProjectileMesh;

UPROPERTY(EditAnywhere,Category="Combat")
class UParticleSystem* HitParticle;

UPROPERTY(VisibleAnywhere,Category="Movement")
class UProjectileMovementComponent* ProjectileMoveComp;

UPROPERTY(VisibleAnywhere,Category="Combat")
class UParticleSystemComponent* TrailParticle;

UPROPERTY(EditAnywhere,Category="Combat")
TSubclassOf<class UCameraShake> HitCameraShake;

UPROPERTY(EditAnywhere)
float Damage = 25.0f;

UFUNCTION()
void OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalHitimpulse,const FHitResult& Hit);

};
