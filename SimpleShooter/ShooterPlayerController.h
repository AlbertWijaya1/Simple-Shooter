// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;		//an override in the function means that it is being overwritten somwhere in the code too.
	
	private:
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget>LoseScreenClass;			//as an alternative to TSubClassOf, we can use 'UCLASS' but this doesn't restrict what kind of class we can use and here we want to restrict it to only being UUserWidget which is the parent class of the widget we want to spawn (WBP_LoseScreen)
};
