// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Turret.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameMode::PawnDeath(AActor* DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDeath();
        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnableState(false);
            GameOver(false);
            FTimerHandle RestartHandle;
            FTimerDelegate RestartDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,&AToonTanksPlayerController::RestartLevel);
            GetWorldTimerManager().SetTimer(RestartHandle,RestartDelegate,DelayTime,false);
           
        }
    }
    else if(ATurret* DeadTurret = Cast<ATurret>(DeadActor))
    {
        DeadTurret->HandleDeath();
        NumTurret--;
        if(NumTurret == 0) GameOver(true);
    }
}


void AToonTanksGameMode::HandleGameStart()
{
    NumTurret = GetNumberOfTurrets();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));
    StartGame();
    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnableState(false);

        FTimerHandle  PlayerEnableTimeHandle;
        FTimerDelegate PlayerEnableTimeDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnableState,
            true);
        GetWorldTimerManager().SetTimer(PlayerEnableTimeHandle,PlayerEnableTimeDelegate,DelayTime,false);
    }
}

int32 AToonTanksGameMode::GetNumberOfTurrets() const
{
    TArray<AActor*> Turrets;
    UGameplayStatics::GetAllActorsOfClass(this,ATurret::StaticClass(),Turrets);
    return Turrets.Num();
}
