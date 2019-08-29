// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;


/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ATank* GetControlledTank() const;

    virtual void Tick(float DeltaTime) override;

private:
    void AimTowardsCrosshair(float DeltaTime);
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;
    bool GetLookPositionAndDirection(FVector& OutLookPosition, FVector& OutLookDirection) const;
    bool GetLookHitLocation(FVector& OutHitLocation, const FVector& LookPosition, const FVector& LookDirection, float TraceDistance = 10000.0f) const;

protected:
    UPROPERTY(EditAnywhere)
    float CrosshairXLocation = 0.5f;

    UPROPERTY(EditAnywhere)
    float CrosshairYLocation = 0.33f;

    UPROPERTY(EditAnywhere)
    float LineTraceRange = 100000.0f;
};
