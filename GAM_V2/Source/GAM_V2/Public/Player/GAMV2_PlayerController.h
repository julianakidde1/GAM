// Copyright Juliana Kidde

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GAMV2_PlayerController.generated.h"

//forward declarations
class UInputMappingContext; 
class UInpuAction;
struct FInputActionValue;
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
	virtual void SetupInputComponent() override; //to retrieve inputMappingContext data
	
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> GAM_V2Context;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	void Move(const FInputActionValue& InputActionValue); 
};
