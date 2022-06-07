// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    UE_LOG(LogTemp, Warning, TEXT("Pawn Has been killed!"));
    
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());                           //need to get the controller of the pawn that was killed
    if(PlayerController != nullptr){
        // PlayerController->GameHasEnded(nullptr, false);                     //a way to tell if the game has ended or not, false means that nope the game has not ended. A->B means that B function or variable is  part of A class and we want to use or call the function or variable. This has been replaced by the bIsWinner on the EndGame function down there on Lecture 217.
        EndGame(false);         //means that the player has actually lose the game (Setting bIsPlayerWinner to false). This player can either be playercontroller or an AI
    }

    for(AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld())) {      //This is saying that we will do a for loop over every controller in the world (iterate through all the controller) in the variable called 'Controller'. This will return us a range object, sort of like a list that goes over all over the controllers in the world (that's why we put 'GetWorld()')
        if(!AIController->IsDead()){                //if there is an AIController that is not dead yet, return early.. which means that we have yet won! once all AIController is dead (AIController->IsDead), then only we won the game, which we define down there in the 'else' part by setting bIsPlayerWinner to true.
            return;
        }
        else{
            EndGame(true);      //player wins the game (Setting bIsPlayerWinner to true).
        }

    }
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)              //bIsPlayerWinner indicates that a player has won the game (can either be the AI or the controller (us))
{
    for(AController* Controller : TActorRange<AController>(GetWorld()))       //This is saying that we will do a for loop over every controller in the world (iterate through all the controller) in the variable called 'Controller'. This will return us a range object, sort of like a list that goes over all over the controllers in the world (that's why we put 'GetWorld()')
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;       //check if the winning pawn (bIsPlayerWinner)(the one who kills all other pawn) is the player (==Controller->IsPlayerController()). Since we make bIsWinner to be A==B, if one of it fails, it will return false. So both A & B must be true.
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);                   //Controller->GetPawn() is to focus the camera to our pawn. Otherwise, just simply use 'nullptr'
        
        //Alternative:
    //     bool bIsPlayerController = Controller->IsPlayerController();           //returns true if it is the pawn we are controlling (aka the player controller).
    //     if(bIsPlayerWinner){
    //         Controller->GameHasEnded(nullptr, bIsPlayerController);             //returns (GameHasEnded(nullptr, true)) if the subjectof intrest is the playercontroller and not the AI. Means that we declare the game is over if bIsPlayerWinner == true and the one controlling is the player (bIsPlayerController == true);
    //     }
    //     else{
    //         Controller->GameHasEnded(nullptr, !bIsPlayerController);
    //     }
    }
}
