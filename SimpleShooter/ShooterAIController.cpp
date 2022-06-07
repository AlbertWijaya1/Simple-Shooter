// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"


void AShooterAIController::BeginPlay() 
{
    Super::BeginPlay();

    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);

        APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaSeconds) 
{
    Super::Tick(DeltaSeconds);
    //     /*this part has been superseeded by BTService_PlayerLocation and BTService_PlayerLocationIfSeen. 
    // It is better this way since the tick funciton will only be running when its flow is on! which is much more efficient,
    // compare to running it at tick function all the time. */

    // APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //GetPlayerPawn(WorldContextObject, PlayerIndex(0 means player 0)). GetPawn is referring to the pawn , while player pawn is referring to the pawn that is being controlled by the player we specified (itc player 0)
    // if(LineOfSightTo(PlayerPawn)){       //only do the following function if the player is on sight

    //     GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());     //Storing the  PlayerPawn->GetActorLocation() inside PlayerLocation is for setting a new "key" in the blackboard (open blackboard and you'll know what i mean). The 'playerlocation' name must be similar to the new key u created in the blackboard unless it will return '(invalid)'. itc we want the vector of the player in the world. We set it in the tick such that the player's location will be updated everytime and not only defined once when the game starts.
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());     //Storing the  PlayerPawn->GetActorLocation() inside LastKnownPlayerLocation. This is for setting a new "key" in the blackboard (open blackboard and you'll know what i mean). The 'playerlocation' name must be similar to the new key u created in the blackboard unless it will return '(invalid)'. itc we want the vector of the player in the world. We set it in the tick such that the player's location will be updated everytime and not only defined once when the game starts.
    //     // SetFocus(PlayerPawn);           //THIS LINE USED B4 AI IS INTRODUCED. SetFocus is a function under AIController.h which will set its focus to the 'NewFocus' (check the SetFocus Definition to get what i mean by this new focus). ITC, we set the NewFocus to be the PlayerPawn aka the player 0. The priority is set to default which is the GamePlay which is what we want, means that it will set the focus to the gameplay as priority. You can check on other priority option at the definition f12.
    //     // MoveToActor(PlayerPawn, AcceptanceRadius);        //THIS LINE USED B4 AI IS INTRODUCED. Move closer to the actor with x tolerance (aka distance to the actor, which UE call 'acceptance radius'). We first need to set the navmesh in the scene, unless UE won't be able to know which part has collision and which part is hasn't. Using this funciton, we are able to tell unreal that we want the AI to follow the route govern by the navmesh to the actor as close as the 'Acceptance Radius'.

    // }

    // else{
    //     // ClearFocus(EAIFocusPriority::Gameplay); // THIS LINE USED B4 AI IS INTRODUCED. Clear the focus priority (itc the game play)
    //     // StopMovement();                         // THIS LINE USED B4 AI IS INTRODUCED. Stop the movement of the actor
    //     GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));       //clear the keys, itc its the player location... leaving just the LastKnownPlayerLocation when the playerpawn is onsight and delete the one that is offsight.
    // }

}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
    if(ControlledCharacter != nullptr){
        return ControlledCharacter->IsDead();              //run the IsDead() function on AShooterCharacter class where we cast and store it inside the 'ControlledCharacter' variable. If you check ShooterCharacter class, ull see that there's a IsDead function and that is the function we are running.
    }

    return true;    //saying that if we don't have a pawn, if we are not controlling a pawn essentially this AIController is as good as dead which is possible and certainly could happen coz the pawn dettaches from the AI controller when it dies.
}





















// // Fill out your copyright notice in the Description page of Project Settings.


// #include "ShooterAIController.h"
// #include "Kismet/GameplayStatics.h"
// #include "BehaviorTree/BlackboardComponent.h"

// void AShooterAIController::BeginPlay()
// {
//     Super::BeginPlay();
//     //  APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //GetPlayerPawn(WorldContextObject, PlayerIndex(0 means player 0))
//     if(AIBehavior != nullptr){
//         RunBehaviorTree(AIBehavior);
//         GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());     //GetPawn is referring to the pawn , while player pawn is referring to the pawn that is being controlled by the player we specified (itc player 0)
//     }
// }

// void AShooterAIController::Tick(float DeltaSeconds)
    
// {
//     Super::Tick(DeltaSeconds);


//     /*this part has been superseeded by BTService_PlayerLocation and BTService_PlayerLocationIfSeen. 
//     It is better this way since the tick funciton will only be running when its flow is on! which is much more efficient,
//     compare to running it at tick function all the time. */

//     APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0); //GetPlayerPawn(WorldContextObject, PlayerIndex(0 means player 0)). GetPawn is referring to the pawn , while player pawn is referring to the pawn that is being controlled by the player we specified (itc player 0)
//     if(LineOfSightTo(PlayerPawn)){       //only do the following function if the player is on sight

//         GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());     //Storing the  PlayerPawn->GetActorLocation() inside PlayerLocation is for setting a new "key" in the blackboard (open blackboard and you'll know what i mean). The 'playerlocation' name must be similar to the new key u created in the blackboard unless it will return '(invalid)'. itc we want the vector of the player in the world. We set it in the tick such that the player's location will be updated everytime and not only defined once when the game starts.
//         GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());     //Storing the  PlayerPawn->GetActorLocation() inside LastKnownPlayerLocation. This is for setting a new "key" in the blackboard (open blackboard and you'll know what i mean). The 'playerlocation' name must be similar to the new key u created in the blackboard unless it will return '(invalid)'. itc we want the vector of the player in the world. We set it in the tick such that the player's location will be updated everytime and not only defined once when the game starts.
//         // SetFocus(PlayerPawn);           //THIS LINE USED B4 AI IS INTRODUCED. SetFocus is a function under AIController.h which will set its focus to the 'NewFocus' (check the SetFocus Definition to get what i mean by this new focus). ITC, we set the NewFocus to be the PlayerPawn aka the player 0. The priority is set to default which is the GamePlay which is what we want, means that it will set the focus to the gameplay as priority. You can check on other priority option at the definition f12.
//         // MoveToActor(PlayerPawn, AcceptanceRadius);        //THIS LINE USED B4 AI IS INTRODUCED. Move closer to the actor with x tolerance (aka distance to the actor, which UE call 'acceptance radius'). We first need to set the navmesh in the scene, unless UE won't be able to know which part has collision and which part is hasn't. Using this funciton, we are able to tell unreal that we want the AI to follow the route govern by the navmesh to the actor as close as the 'Acceptance Radius'.

//     }

//     else{
//         // ClearFocus(EAIFocusPriority::Gameplay); // THIS LINE USED B4 AI IS INTRODUCED. Clear the focus priority (itc the game play)
//         // StopMovement();                         // THIS LINE USED B4 AI IS INTRODUCED. Stop the movement of the actor
//         GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));       //clear the keys, itc its the player location... leaving just the LastKnownPlayerLocation when the playerpawn is onsight and delete the one that is offsight.
//     }
// }

