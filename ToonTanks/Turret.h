// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

	public:
	virtual void Tick(float DeltaTime) override;
	void HandleDeath();

	protected:
	virtual void BeginPlay() override;

	private:

	class ATank* Tank;
	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere,Category = "Combat")
	float TurretRadius = 400.0f;

	UPROPERTY()
	float FireRate = 2.0f;

	void CheckForFireCondition();
	bool IsInRange();
};
