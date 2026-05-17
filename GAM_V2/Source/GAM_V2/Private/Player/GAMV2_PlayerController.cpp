// Copyright Juliana Kidde


#include "Player/GAMV2_PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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
	Subsystem->AddMappingContext(GAM_V2Context, 0); // how we add the mapping context so the play controller can retrieve data 
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default; //choosing the type of mouse cursor
	
	FInputModeGameAndUI InputModeData; 
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false); //the cursor remains visible when captured in the viewport
	SetInputMode(InputModeData);
	
}

void AGAMV2_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent) ; // accessing the inputComponent var and casting it to enhanced input + checking if cast fails
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGAMV2_PlayerController::Move); // binding it to the move function so it can access the data/keystrokes
}

void AGAMV2_PlayerController::Move(const FInputActionValue& InputActionValue) 
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>(); //FVector2D is the data type we used in the inputAction asset
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);//figuring out the forward direction of the player
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	//adding the movement input to the pawn
	if (APawn* ControlledPawn = GetPawn<APawn>())// not doing an assert because move is called frame and might be called before the pawn is valid
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
