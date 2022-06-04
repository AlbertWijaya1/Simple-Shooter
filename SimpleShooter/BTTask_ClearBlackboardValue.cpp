// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()            //this is a constructor
{
    NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);                                              //when you see virtual+override usually need super to call in the 'Super::' to reccall back the behavior, coz override removed that behavior. Execute task is called when the task starts to execute.
    OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("GetSelectedBlackboardKey()"));     //get the blackboard. GetSelectedBlackboardKey() is the name of the selected blackboard key (We got this from UBTTask_BlackboardBase.h (find this function on the 'BTTask_BlackboardBase.h' and f12)).
    
    return EBTNodeResult::Succeeded;            //return a signal that this node has succeeded. We call succeeded coz we only need to call this task any longer than a single tick (frame)
    
}
