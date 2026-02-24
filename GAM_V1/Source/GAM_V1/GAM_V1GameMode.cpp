// Copyright Epic Games, Inc. All Rights Reserved.

#include "GAM_V1GameMode.h"

#include "Kismet/GameplayStatics.h"
#include "GAM_V1Character.h"
#include "ShooterAI.h"

AGAM_V1GameMode::AGAM_V1GameMode()
{
	// stub
}

void AGAM_V1GameMode::BeginPlay()
{
	Super::BeginPlay();

	AGAM_V1Character* Player = Cast<AGAM_V1Character>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); // Getting the player [since we do it in the BeginPlay of the GameMode we only have to do it once; doing it in the ShooterAI would require it to be done multiple times for each enemy instance. we will them loop over the enemy actors and give them the player character]

	TArray<AActor*> ShooterAIActors; 
	 UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAIActors); // saving all the shooter actors for the AI conttoller into the array. 


	 for (int32 LoopIndex = 0; LoopIndex < ShooterAIActors.Num(); LoopIndex++)
	 {
		AActor* ShooterAIActor = ShooterAIActors[LoopIndex] ;
		AShooterAI* ShooterAI = Cast<AShooterAI>(ShooterAIActor);

		if (ShooterAI)
		{
			ShooterAI->StartBehaviorTree(Player);
		}
	 }
}