// Copyright Juliana Kidde


#include "Player/GAMV2_PlayerController.h"

#include "EnhancedInputSubsystems.h"

AGAMV2_PlayerController::AGAMV2_PlayerController()
{
	bReplicates = true;
}

void AGAMV2_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(GAM_V2Context); // will halt execution if GAM_V2Context is a nullpointer
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem)
	Subsystem->AddMappingContext(GAM_V2Context, 0); 
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default; //choosing the type of mouse cursor
	
	FInputModeGameAndUI InputModeData; 
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false); //the cursor remains visible when captured in the viewport
	SetInputMode(InputModeData);
	
}
