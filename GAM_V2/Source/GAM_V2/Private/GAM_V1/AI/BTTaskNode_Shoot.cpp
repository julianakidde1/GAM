// Fill out your copyright notice in the Description page of Project Settings.



#include "GAM_V1/AI/BTTaskNode_Shoot.h"

#include "GAM_V1/ShooterAI.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
	NodeName = TEXT("Shoot At Player");
}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	EBTNodeResult::Type Result = EBTNodeResult::Failed;

	AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	if (OwnerController)
	{
		AGAM_V1Character* OwnerCharacter = OwnerController->MyCharacter;
		AGAM_V1Character* PlayerCharacter = OwnerController->PlayerCharacter;

		if (OwnerCharacter && PlayerCharacter && PlayerCharacter->IsAlive)
		{
			OwnerCharacter->Shoot();
			Result = EBTNodeResult::Succeeded;
		}
	}

	return Result;
}
