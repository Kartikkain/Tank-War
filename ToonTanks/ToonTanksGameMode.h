// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void PawnDeath(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWinGame);

private:

	float DelayTime = 3.0f;
	int32 NumTurret = 0;

	class ATank* Tank = nullptr;

	class AToonTanksPlayerController* ToonTanksPlayerController = nullptr;

	void HandleGameStart();

	int32 GetNumberOfTurrets() const;
	
};
