// // Fill out your copyright notice in the Description page of Project Settings.

// #pragma once

// #include "CoreMinimal.h"
// #include "GameFramework/Character.h"
// #include "Gun.h"
// #include "ShooterCharacter.generated.h"

// UCLASS()
// class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
// {
// 	GENERATED_BODY()

// public:
// 	// Sets default values for this character's properties
// 	AShooterCharacter();

// protected:
// 	// Called when the game starts or when spawned
// 	virtual void BeginPlay() override;

// public:	
// 	// Called every frame
// 	virtual void Tick(float DeltaTime) override;

// 	// Called to bind functionality to input
// 	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// 	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

// 	void Shoot();

// 	UFUNCTION(BlueprintPure)
//  	bool IsDead()const;
	
// 	bool bIsAmmoReceived;

// 	// TArray<AGun*>Guns;
// 	// TArray<TSubclassOf<AGun>>GunArray;		//<TSubClassOf<class u want to put to the BP>VariableName;


	
// private:
// 	void MoveForward(float AxisValue);
// 	void LookUp(float AxisValue);
// 	void MoveRight(float AxisValue);
// 	// void Jump(float AxisValue);

	
// 	UPROPERTY(EditDefaultsOnly)
// 	TSubclassOf<class AGun>GunClass;			//here we are storing the AGun UClass in variable called GunClass. This allows all the associated class related to AGun to be called, including the child and instances, in this case since we create the blueprint version of AGun, we can also assign the blueprint to the GunClass variable. Thus, using this approach we can then call the blueprint side of the class in our other cpp class (by calling the ProjectileClass variable)

// 	// UPROPERTY(EditDefaultsOnly)
// 	// TSubclassOf<class AGun>GunsClass;			//here we are storing the AGun UClass in variable called GunClass. This allows all the associated class related to AGun to be called, including the child and instances, in this case since we create the blueprint version of AGun, we can also assign the blueprint to the GunClass variable. Thus, using this approach we can then call the blueprint side of the class in our other cpp class (by calling the ProjectileClass variable)


// 	// UPROPERTY()
// 	// class AGun* Gun;

// 	UPROPERTY()
// 	class AGun* Gun;


// 	// TArray<AGun*> Guns{};
// 	// int Size = 0;
// 	// TArray<TSubclassOf<AGun>> GunClasses;

// 	UPROPERTY(EditAnywhere)
// 	float MaxHealth = 100;

// 	UPROPERTY(VisibleDefaultsOnly)
// 	float Health;

// 	UFUNCTION(BlueprintPure)
// 	float GetHealthPercent() const;				//const bcs it shouldn't change in any way when being called.

// 	UPROPERTY(EditAnywhere)
// 	int MaxAmmo=100.f;

// 	UPROPERTY(VisibleDefaultsOnly)
// 	int Ammo;

// 	UFUNCTION(BlueprintPure)
// 	int GetAmmoQuantity() const;

// 	UPROPERTY(EditAnywhere)
// 	USoundBase* OutOfAmmoSound;

// 	void AmmoReceived();

// 	UPROPERTY(EditAnywhere)
// 	USoundBase* ReloadAmmoSound;

// 	// TArray<class AGun*>Weapons;

// 	// bool Dead = false;
// };


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

	void Shoot();

	UFUNCTION(BlueprintPure)
 	bool IsDead()const;
	
	bool bIsAmmoReceived;

	// TArray<AGun*>Guns;
	// TArray<TSubclassOf<AGun>>GunArray;		//<TSubClassOf<class u want to put to the BP>VariableName;


	
private:
	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void MoveRight(float AxisValue);
	// void Jump(float AxisValue);

	void ChangeWeapon();
	

	// UPROPERTY(EditDefaultsOnly)
	// TSubclassOf<class AGun>GunsClass;			//here we are storing the AGun UClass in variable called GunClass. This allows all the associated class related to AGun to be called, including the child and instances, in this case since we create the blueprint version of AGun, we can also assign the blueprint to the GunClass variable. Thus, using this approach we can then call the blueprint side of the class in our other cpp class (by calling the ProjectileClass variable)


	UPROPERTY()
	class AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun>GunClass;			//here we are storing the AGun UClass in variable called GunClass. This allows all the associated class related to AGun to be called, including the child and instances, in this case since we create the blueprint version of AGun, we can also assign the blueprint to the GunClass variable. Thus, using this approach we can then call the blueprint side of the class in our other cpp class (by calling the ProjectileClass variable)
	int i=0;
	int j=0;
	// UPROPERTY(EditDefaultsOnly)
	int ActiveGunIndex;
	UPROPERTY(VisibleDefaultsOnly)
	TArray<AGun*> Guns;					//this is as a variable to store the gun we manually specified in gunclasses. whatever action we want to do next with the gun (spawning, attaching, hiding, etc) will be done with these Guns array that store the variable of the member of the gunclasses
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AGun>> GunClasses;			//we put TSubClassOf is like to bring in th ewhole AGun class to represent AGUn in the blueprint, such that we can call the blueprint class in each array. Confused? look at TSubClassOf at the BasePawn.h @ ToonTanks

	
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	UPROPERTY(VisibleDefaultsOnly)
	float Health;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;				//const bcs it shouldn't change in any way when being called.

	UPROPERTY(EditAnywhere)
	int MaxAmmo=100.f;

	UPROPERTY(VisibleDefaultsOnly)
	int Ammo;

	UFUNCTION(BlueprintPure)
	int GetAmmoQuantity() const;

	UPROPERTY(EditAnywhere)
	USoundBase* OutOfAmmoSound;

	void AmmoReceived();

	UPROPERTY(EditAnywhere)
	USoundBase* ReloadAmmoSound;

	// TArray<class AGun*>Weapons;

	// bool Dead = false;
};

