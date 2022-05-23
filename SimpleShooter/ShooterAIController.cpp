// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //GetPlayerPawn(WorldContextObject, PlayerIndex(0 means player 0))

    SetFocus(PlayerPawn);           //SetFocus is a function under AIController.h which will set its focus to the 'NewFocus' (check the SetFocus Definition to get what i mean by this new focus). ITC, we set the NewFocus to be the PlayerPawn aka the player 0. The priority is set to default which is the GamePlay which is what we want.
}

void AShooterAIController::Tick(float DeltaTime)
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //GetPlayerPawn(WorldContextObject, PlayerIndex(0 means player 0))
    MoveToActor(PlayerPawn, 200);        //move closer to the actor with x tolerance (aka distance to the actor, which UE call 'acceptance radius'). We first need to set the navmesh in the scene, unless UE won't be able to know which part has collision and which part is hasn't. Using this funciton, we are able to tell unreal that we want the AI to follow the route govern by the navmesh to the actor as close as the 'Acceptance Radius'.
    
}
