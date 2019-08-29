#include "TankAIController.h"

#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const
{    
    if( APlayerController* playerController = GetWorld()->GetFirstPlayerController() )
    {
        return Cast<ATank>(playerController->GetPawn());
    }
    return nullptr;
}