// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f,ToTarget.Rotation().Yaw,0.0f);
	TurretMesh->SetWorldRotation(LookAtRotation);
}


void ABasePawn::Fire()
{
	FVector Location = SpawnPoint->GetComponentLocation();
	FRotator Rotation = SpawnPoint->GetComponentRotation();
	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,Location,Rotation);
	projectile->SetOwner(this);
}

void ABasePawn::HandleDeath()
{
	if(DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,DeathParticle,GetActorLocation(),GetActorRotation());
	}
	if(DeathCameraShake)
	{
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathCameraShake);
	}
}