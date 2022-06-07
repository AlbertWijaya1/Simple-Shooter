// Fill out your copyright notice in the Description page of Project Settings.
//this class is being made under SimpleShooterGameModeBase, so any function and variable here will also inherit from SimpleShooterGameModeBase (like the PawnKilled which is inherited by SimpleShooterGameModeBase)

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()
	virtual void PawnKilled(APawn* PawnKilled)override;

	private:
	void EndGame(bool bIsPlayerWinner);			//a way of telling whether the AI that has won or the player that has won.
};

