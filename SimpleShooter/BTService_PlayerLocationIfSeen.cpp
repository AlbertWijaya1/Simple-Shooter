// Fill out your copyright notice in the Description page of Project Settings.
// we have this service as an alternative to putting the function we waant to call in the tick function. By putting the funciton here instead, the function will only be called if the blackboard flows to that service, otherwise it won't run, this way it will be much more efficient


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"



UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update Last Known Player location");
}




void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    AAIController* AIOwner = OwnerComp.GetAIOwner();
    APawn* AIPawn = AIOwner->GetPawn();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(AIOwner->LineOfSightTo(PlayerPawn)){         //check if player(the pawn we control) is onsight
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);           //before lecture 225 it is (SetValueAsVector, PlayerPawn->GetActorLocation()). But since we don't want updateplayerlocation to be updating the player location, we change to object instead to make the AI update towards the player 'object', not just the location. Coz if location then the Actor rotation wont update and it will just move towards the actor being focusing at one point (can't rotate). Basically we switch to SetValueAsObject to make it able to update its rotation when moving towards the PlayerController ( in the BT_EnemyAI we also update the 'player'  keys from vector to object to encompensate this idle rotation issue as well) and since in the UpdatePlayerLocationIfSeen service in the behavior tree is a custom service made in cpp, we then need to change the syntax in the cpp file as well to redefine its meaning... otherwise if not custom can just edit from the blueprint itself.
    }

    else{
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}


