// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"

#include "Kismet/GameplayStatics.h"

void AShooterAI::BeginPlay()
{
    Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); 
    if (PlayerPawn) //the player pawn will be what the enemyAI focus on
    {
        SetFocus(PlayerPawn);
        
    }

}

void AShooterAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); 
    if (PlayerPawn) //the player pawn will be what the enemyAI focus on
    {
        MoveToActor(PlayerPawn, 200.0f);
        
    }


}
