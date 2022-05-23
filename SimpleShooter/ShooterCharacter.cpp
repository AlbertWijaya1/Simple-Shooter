// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "ShooterCharacter.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);		//spawn the gun, if the location and rotation is not specified, it will just spawn at global coordinate 0,0,0
	
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);		//hide the weapon_r skeletalmesh, if you see Exxx its an Enum and need to be followed by double colon (Exxx::)
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));		// Attach the gun to the GetMesh(), aka the mesh of this cpp file, itc the ShooterCharacter. KeepRelativeTransform means we are keeping the location of the actor being spawned relative to the GetMesh to be constant. Otherwise, the other option is "KeepWorldTransform" which is keeping the location of the actor being spawned constand to the world, i.e the actor stays at the same spawn point in the world
	Gun->SetOwner(this);	// setting the gun's owner to be the ShooterCharacter. Such that when we call 'getowner' in the gun.cpp, it means that we are calling the owner of the gun and that is this ShooterCharacter. 

	Health = MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);			//automatically pass in the 'AxisValue' to the MoveForward function as the parameter. so it automatically do: "MoveForward(AxisValue);"
    PlayerInputComponent -> BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);			
	PlayerInputComponent -> BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);				//automatically pass in the 'AxisValue' to the LookUp function as the parameter. so it automatically do: "LoopUp(AxisValue);"
    PlayerInputComponent -> BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AShooterCharacter::Shoot);

}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);		//setting the damageapplied value to be whichever smaller between DamageToApply or Health.
	Health-=DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health %f"), Health);

	return DamageToApply;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector()* AxisValue);
}

// void AShooterCharacter::LookUp(float AxisValue)
// {
// 	AddControllerPitchInput(AxisValue);
// }

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector()* AxisValue);
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}


