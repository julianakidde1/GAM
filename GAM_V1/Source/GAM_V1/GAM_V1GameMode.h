// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GAM_V1GameMode.generated.h"

/**
 *  Simple GameMode for a first person game
 */
UCLASS(abstract)
class AGAM_V1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGAM_V1GameMode();
};



