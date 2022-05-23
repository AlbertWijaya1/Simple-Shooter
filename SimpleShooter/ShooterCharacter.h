// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gun.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void MoveRight(float AxisValue);
	// void Jump(float AxisValue);

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun>GunClass;			//here we are storing the AGun UClass in variable called GunClass. This allows all the associated class related to AGun to be called, including the child and instances, in this case since we create the blueprint version of AGun, we can also assign the blueprint to the GunClass variable. Thus, using this approach we can then call the blueprint side of the class in our other cpp class (by calling the ProjectileClass variable)

	UPROPERTY()
	class AGun* Gun;

	void Shoot();

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	UPROPERTY(VisibleDefaultsOnly)
	float Health;

	UFUNCTION(BlueprintPure)
 	bool IsDead()const;

	// bool Dead = false;
};
