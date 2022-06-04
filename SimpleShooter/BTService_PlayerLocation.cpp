
// Fill out your copyright notice in the Description page of Project Settings.
// we have this service as an alternative to putting the function we waant to call in the tick function. By putting the funciton here instead, the function will only be called if the blackboard flows to that service, otherwise it won't run, this way it will be much more efficient

#include "BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"


UBTService_PlayerLocation::UBTService_PlayerLocation()
{
    NodeName = TEXT("Update Player location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(PlayerPawn == nullptr){return;}
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
}
