// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h"

void AToonTanksPlayerController::SetPlayerEnableState(bool bplayerenable)
{
    if(bplayerenable) GetPawn()->EnableInput(this);
    else GetPawn()->DisableInput(this);

    bShowMouseCursor = bplayerenable;
}

