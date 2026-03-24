// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MissionManager.generated.h"

/**
 * 
 */
UCLASS()
class GAM_V1_API UMissionManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	void StartMission(int32 MissionID);

private: 
	void LoadMissionData(); 

	UPROPERTY(BlueprintReadOnly)
	int32 EnemiesKilled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 TotalEnemies;
	
};
