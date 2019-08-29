#include "TankPlayerController.h"

#include "Tank.h"
#include "HAL/IConsoleManager.h"
#include "DrawDebugHelpers.h"


static TAutoConsoleVariable<int32> CVarTankPlayerControllerDebugDraw(
    TEXT("BattleTank.TankPlayerController.DebugDraw"),
    0,
    TEXT("This variable enables (1) or disables (0) debug drawing for the TankPlayerController")
);


ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimTowardsCrosshair(DeltaTime);
}

void ATankPlayerController::AimTowardsCrosshair(float DeltaTime)
{
    ATank* ControlledTank = GetControlledTank();
    if( !ControlledTank )
    {
        return;
    }

    FVector HitLocation;
    if( GetSightRayHitLocation( HitLocation ) )
    {      
        if( CVarTankPlayerControllerDebugDraw.GetValueOnGameThread() )
        {
            DrawDebugSphere(GetWorld(), HitLocation, 50.0f, 16, FColor::Red);
        }
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    FVector WorldLocation;
    FVector WorldDirection;

    if( GetLookPositionAndDirection(WorldLocation, WorldDirection) )
    {   
        return GetLookHitLocation(OutHitLocation, WorldLocation, WorldDirection, LineTraceRange);
    }

    return false;
}

bool ATankPlayerController::GetLookHitLocation(FVector& OutHitLocation, const FVector& LookPosition, const FVector& LookDirection, float TraceDistance) const
{        
    const FVector LookEndPosition = LookPosition + LookDirection * TraceDistance;
    FHitResult HitResult;

    if( GetWorld()->LineTraceSingleByChannel(
            HitResult, 
            LookPosition, 
            LookEndPosition,
            ECollisionChannel::ECC_Visibility) )
    {
        OutHitLocation = HitResult.ImpactPoint;
        return true;
    }    

    return false;
}

bool ATankPlayerController::GetLookPositionAndDirection(FVector& OutLookPosition, FVector& OutLookDirection) const
{
    int32 ViewportWidth, ViewportHeight;
    GetViewportSize(ViewportWidth, ViewportHeight);

    return DeprojectScreenPositionToWorld(
        CrosshairXLocation * ViewportWidth,
        CrosshairYLocation * ViewportHeight,
        OutLookPosition,
        OutLookDirection
    );
}
