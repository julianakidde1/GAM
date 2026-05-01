// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_PlayerLocationIfSeen.h"

#include "ShooterAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update PlayerLocation If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());
    AGAM_V1Character* Player = OwnerController->PlayerCharacter;
    UBlackboardComponent* Blackboard = OwnerController->GetBlackboardComponent();

    if (OwnerController && Player && Blackboard) // setting the player location if enemy has line of sight and unsetting it if the enemy doesn't.
    {
        if (OwnerController->LineOfSightTo(Player)) 
       {
            Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
            OwnerController->SetFocus(Player);
       }

       else
       {
            Blackboard->ClearValue(GetSelectedBlackboardKey());
            OwnerController->ClearFocus(EAIFocusPriority::Gameplay);
       }
        
    }

}
