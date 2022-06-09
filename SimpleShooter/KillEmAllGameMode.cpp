// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)          // a function which defines what happen when a pawn dies. The pawn here can be either the player (denoted by 'PlayerController' below) or an AI (denoted by 'AIController' below).
{
    Super::PawnKilled(PawnKilled);
    UE_LOG(LogTemp, Warning, TEXT("Pawn Has been killed!"));
    
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());                           //need to get the controller of the pawn that was killed to refer to the playercontroller
    if(PlayerController != nullptr){                                            //What happen if the pawn that dies is the player.
        // PlayerController->GameHasEnded(nullptr, false);                     //a way to tell if the game has ended or not, false means that nope the game has not ended. A->B means that B function or variable is  part of A class and we want to use or call the function or variable. This has been replaced by the bIsWinner on the EndGame function down there on Lecture 217.
        EndGame(false);         //means that the player has actually lose the game (Setting bIsPlayerWinner to false). This player can either be playercontroller or an AI
    }
    for(AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld())) {      //This is saying that we will do a for loop over every AIcontroller in the world (iterate through all the AIcontroller) in the variable called 'AIController'. This will return us a range object, sort of like a list that goes over all over the AIcontrollers in the world (that's why we put 'GetWorld()')
        if(!AIController->IsDead()){                //if there is an AIController that is not dead yet, return early.. which means that we have yet won! once all AIController is dead (AIController->IsDead), then only we won the game, which we define down there in the 'else' part by setting bIsPlayerWinner to true. IsDead is a function we define on ShooterAIController.h and .cpp
            return;                                 // return early, aka exit the if statement (the game isn't over just yet).
        }
    }
    
        EndGame(true);      //player wins the game (Setting bIsPlayerWinner to true). If 2 of the if statement above returns false, then this will execute, meaning that the pawn being killed is NOT the player controller and that there is no AIController remaining (aka that all AIController->IsDead()). If any of the if statement above returns true, then it will execute that code instead and won't even reached this part of the code. That is why this part is being placed at the very bottom so that the code will go through all the if statement from the top to ensure that the pawn being killed is not the playercontroller and that all AIController has all dies, if this satisfy, then will the EndGame(true) be executed which means that we have won the game (setting bIsPlayerWinner = true).
    

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
