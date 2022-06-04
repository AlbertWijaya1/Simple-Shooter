// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "ShooterCharacter.h"
#include "AIController.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);                                              //when you see virtual+override usually need super to call in the 'Super::' to reccall back the behavior, coz override removed that behavior. Execute task is called when the task starts to execute.
    AAIController* AIOwner = OwnerComp.GetAIOwner();        //this is similar to GetOwner() but for AI(?).
    Character = Cast<AShooterCharacter> (AIOwner->GetPawn());            //Defining 'Character' to be the pawn of the AI which leads us to the pawn(ShooterCharacter) where we code the shoot function in.
    
    if(AIOwner == nullptr){
        return EBTNodeResult::Failed;
    }
    if(Character ==nullptr){
        return EBTNodeResult::Failed;
    }
    Character->Shoot();          //we first need to define what is 'Character'! otherwise UE will just treat it as an empty variable... it won't give any value.

    return EBTNodeResult::Succeeded;
}

