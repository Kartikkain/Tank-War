// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATurret::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandle,this,&ATurret::CheckForFireCondition,FireRate,true);
}

void ATurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(IsInRange()) RotateTurret(Tank->GetActorLocation());
}

void ATurret::CheckForFireCondition()
{
    if(IsInRange() && Tank->IsPlayerAlive) Fire();
}

bool ATurret::IsInRange()
{
    if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(),Tank->GetActorLocation());
        if(Distance <= TurretRadius) return true;
    }

    return false;
}

void ATurret::HandleDeath()
{
    Super::HandleDeath();
    Destroy();
}
