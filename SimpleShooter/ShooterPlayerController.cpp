// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)                         //a function to call when the game has ended, listing the list of things to do when the game ends. Game Ends can have 2 possibilities, win or lose. bIsWinner = true is win, while bIsWInner = false is lose.
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    
    if(bIsWinner){
    UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);      //only a certain things can actually own a widget, one of those things is the player controller and since we are in the PlayerController class, we can just simply put 'this'.
    
        if(WinScreen != nullptr){                                           //to prevent the condition where we didn't set the LoseScreenClass to the TSubClassOf
            
            WinScreen->AddToViewport(); 
        }
    
        
    }

    else{
    // UE_LOG(LogTemp, Warning, TEXT("The Game Has Ended"));
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);      //only a certain things can actually own a widget, one of those things is the player controller and since we are in the PlayerController class, we can just simply put 'this'.
        
        if(LoseScreen != nullptr){                                           //to prevent the condition where we didn't set the LoseScreenClass to the TSubClassOf
            
            LoseScreen->AddToViewport(); 
        }
    }
    
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);                           //'SetTimer' calls in a funciton after a certain amount of 'Delay'. Syntax = GetWorldTimerManager().SetTimer( TimerHandle_LifeSpanExpired, this, &AActor::LifeSpanExpired, InLifespan ); @Actor.cpp (FTimerHander (defined at the header file), UWorldObject, &Theclass::the function to call when the delay ended, duration of the delay). Itc, we want to restart the level after 'RestartDelay' second of delay, RestartLevel is a built in function by unreal made in the APlayerController class.
}
