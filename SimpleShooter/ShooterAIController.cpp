// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //GetPlayerPawn(WorldContextObject, PlayerIndex(0 means player 0))

    SetFocus(PlayerPawn);           //SetFocus is a function under AIController.h which will set its focus to the 'NewFocus' (check the SetFocus Definition to get what i mean by this new focus). ITC, we set the NewFocus to be the PlayerPawn aka the player 0. The priority is set to default which is the GamePlay which is what we want.
}
