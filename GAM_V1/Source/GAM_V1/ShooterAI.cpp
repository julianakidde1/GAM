// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"

#include "Kismet/GameplayStatics.h"

void AShooterAI::BeginPlay()
{
    Super::BeginPlay();

    if (EnemyAIBehaviorTree)
    {
        RunBehaviorTree(EnemyAIBehaviorTree);
    }

}

void AShooterAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    /* switching to behavior trees
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); 
    if (PlayerPawn) //the player pawn will be what the enemyAI focus on
    {
       if (LineOfSightTo(PlayerPawn)) // the enemy can only move towards the player if they can see them
       {
            SetFocus(PlayerPawn);
            MoveToActor(PlayerPawn, 200.0f);
       }

       else
       {
            ClearFocus(EAIFocusPriority::Gameplay);
            StopMovement();
       }
        
        
    }
    */


}
