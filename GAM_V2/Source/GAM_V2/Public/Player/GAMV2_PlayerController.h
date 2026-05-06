// Copyright Juliana Kidde

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GAMV2_PlayerController.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class GAM_V2_API AGAMV2_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AGAMV2_PlayerController();
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category="Iput")
	TObjectPtr<UInputMappingContext> GAM_V2Context;
};
