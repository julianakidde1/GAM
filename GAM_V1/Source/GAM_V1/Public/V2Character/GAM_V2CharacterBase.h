// Copyright Juliana Kidde

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GAM_V2CharacterBase.generated.h"

UCLASS(Abstract)
class GAM_V1_API AGAM_V2CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AGAM_V2CharacterBase();

protected:
	virtual void BeginPlay() override;

};
