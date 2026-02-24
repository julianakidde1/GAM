// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAI::BeginPlay()
{
    Super::BeginPlay();
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

void AShooterAI::StartBehaviorTree(AGAM_V1Character *Player) // this function is called in the 'GameMode.cpp', the 'Player' is set there as well
{
    if (EnemyAIBehaviorTree)
    {
        MyCharacter = Cast<AGAM_V1Character>(GetPawn()); // getting the character that this AIController is controlling
        if (Player)
        {
            PlayerCharacter = Player; // setting the argument to the member var
        }

        RunBehaviorTree(EnemyAIBehaviorTree);

        //setting the playerlocation as blackboard key so that the enemies can move towards the player
        UBlackboardComponent* MyBlackboard = GetBlackboardComponent();
        if (MyBlackboard && PlayerCharacter && MyCharacter) //checking that both are valid
        {
            MyBlackboard->SetValueAsVector("PlayerLocation", PlayerCharacter->GetActorLocation());
            MyBlackboard->SetValueAsVector("StartLocation", MyCharacter->GetActorLocation());
        }



    }

}
