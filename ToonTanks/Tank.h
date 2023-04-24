// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	bool IsPlayerAlive = true;

	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	void HandleDeath();
	APlayerController* GetPlayerController() const;

private:

	APlayerController* playerController = nullptr;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere,Category = "Movements")
	float speed = 200.0f;

	UPROPERTY(EditAnywhere,Category = "Movements")
	float RotationSpeed = 200.0f;

	void Move(float value);

	void Turn(float value);
};
