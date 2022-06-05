// Fill out your copyright notice in the Description page of Project Settings.
//this class is being made under SimpleShooterGameModeBase, so any function and variable here will also inherit from SimpleShooterGameModeBase.

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
};
