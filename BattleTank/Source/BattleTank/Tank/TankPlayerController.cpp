#include "TankPlayerController.h"

#include "Tank.h"


ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}