// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "GAM_V1Character.h"

#include "ShooterAI.generated.h"

/**
 * 
 */
UCLASS()
class GAM_V1_API AShooterAI : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public: 	
	virtual void Tick(float DeltaTime) override; 

	UPROPERTY(EditAnywhere)
	UBehaviorTree* EnemyAIBehaviorTree;

	AGAM_V1Character* PlayerCharacter;
	AGAM_V1Character* MyCharacter; // The character the AIController is controlling (the enemy)

	void StartBehaviorTree(AGAM_V1Character* Player);
};
