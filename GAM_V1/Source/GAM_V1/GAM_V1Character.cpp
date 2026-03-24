// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM_V1Character.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAM_V1.h"

#include "GAM_V1PlayerController.h"


AGAM_V1Character::AGAM_V1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void AGAM_V1Character::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AGAM_V1Character::OnDamageTaken); // when a character takes damage, this UFUNCTION will get called 
	
	Health = MaxHealth; 
	UpdateHUD();

	GetMesh()->HideBoneByName("weapon_r", EPhysBodyOp::PBO_None);
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	if (Gun)
	{
		Gun -> SetOwner(this); 
		Gun ->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		Gun->OwnerController = GetController();
	}

	
	
}

void AGAM_V1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AGAM_V1Character::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AGAM_V1Character::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGAM_V1Character::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGAM_V1Character::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AGAM_V1Character::LookInput);

		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AGAM_V1Character::Shoot);

		//Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AGAM_V1Character::DoCrouch);
	}
	else
	{
		UE_LOG(LogGAM_V1, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AGAM_V1Character::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void AGAM_V1Character::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void AGAM_V1Character::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AGAM_V1Character::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void AGAM_V1Character::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void AGAM_V1Character::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void AGAM_V1Character::Shoot()
{
	if(Gun)
		Gun -> PullTrigger(); 
}

void AGAM_V1Character::DoCrouch()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
	else
	{
		Crouch();
	}
}

void AGAM_V1Character::UpdateHUD()
{
	AGAM_V1PlayerController* PlayerController = Cast<AGAM_V1PlayerController>(GetController());
	if (PlayerController)
	{
		float NewPercent = Health / MaxHealth; 
		if (NewPercent < 0.0f)
		{
			NewPercent = 0.0f;
		}
		PlayerController->HUDWidget->SetHealthBarPercent(NewPercent); 
	}
}

void AGAM_V1Character::OnDamageTaken(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *InstigatedBy, AActor *DamageCauser)
{
	if (IsAlive)
	{
		Health -= Damage; 
		UpdateHUD();
		if (Health <= 0.0f) 
		{
			IsAlive = false; 
			Health = 0.0f; 
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); //once the character dies, we turn of the collision
			DetachFromControllerPendingDestroy(); //once dead, player can't move controller

		}

		
	}

}
