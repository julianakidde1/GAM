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

	AGAM_V1Character* MyCharacter; // The character the AIController is controlling (the enemy); so that we don't have to cast it each time we need it
	AGAM_V1Character* PlayerCharacter; // the argument from the 'StartBehaviorTree' function will be saved in here

	void StartBehaviorTree(AGAM_V1Character* Player); // we want to have a 'pointer' to the player character inside of the controller so that it allows us to pass the 'location of the player' into the behavior tree
};
