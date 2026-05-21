// Copyright Juliana Kidde


#include "Character/Jennifer.h"

#include "GameFramework/CharacterMovementComponent.h"

AJennifer::AJennifer()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; //adding character rotation 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true; // constraining movement to plane (might have to remove that later.)
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}
