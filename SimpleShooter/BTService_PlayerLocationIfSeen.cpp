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
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }

    else{
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}


