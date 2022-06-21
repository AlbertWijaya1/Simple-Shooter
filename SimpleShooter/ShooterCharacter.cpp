// // Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooterGameModeBase.h"

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
	// Gun = GetWorld()->SpawnActor<AGun>(GunClass);		//spawn the gun, if the location and rotation is not specified, it will just spawn at global coordinate 0,0,0
	// Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));		// Attach the "Gun" to the GetMesh(), aka the mesh of this cpp file, itc the ShooterCharacter. Such that when the actor is spawned, it doesn't spawn randomly in the world (cos we are not defining the location and rotation at SpawnActor() function, it will spawn at our desire locationa and rotation if we set it at teh SpawnActor() function, but since we didn't we then need to use this 'AttachToComponent()' function to define where we want to spawn the actor when it is present). Plus coz we are using 'KeepRelativeTransform', when we move around it will follow the point where we are attaching the actor to. KeepRelativeTransform means we are keeping the location of the actor being spawned relative to the GetMesh to be constant. Otherwise, the other option is "KeepWorldTransform" which is keeping the location of the actor being spawned constant to the world, i.e the actor stays at the same spawn point in the world
	// Gun->HandleDestruction();		//run the 'HandleDesctruction() function@ Gun.cpp
	// for(int i=0; i<Guns.Num(); i++){
	// Guns[i] = Guns.Emplace(GunClass[i]);
		
	// }
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);		//hide the weapon_r skeletalmesh (the weapon bawaan by the wraith, open 'wraith' and search for weapon_r @ the skeleton tree and ull now what i mean). We need to hide this bcs we're attaching a new gun mesh (which is defined by the 'Gun' variable above) if you see Exxx its an Enum and need to be followed by double colon (Exxx::)
	// Gun->SetOwner(this);	// setting the gun's owner to be the ShooterCharacter. Such that when we call 'getowner' in the gun.cpp, it means that we are calling the owner of the gun and that is this ShooterCharacter. 

	Health = MaxHealth;
	Ammo = MaxAmmo;
	for(int32 j = 0; j<Guns.Num();j++){
		Guns.Emplace(GetWorld()->SpawnActor<AGun>(GunClasses[j]));		//emplacing means adding the array wo creating temporary thingy, if use 'add' it'll create the temporary thingy. and here, we are adding the guns in the GunClasses to the Guns array. 'SpawnActor' means we are Spawning the gun, if the location and rotation is not specified, it will just spawn at global coordinate 0,0,0 (we fill in the location and rotation at BasePawn.cpp @ ToonTanks lecture when we want to spawn the projectile)
		if(Guns[j]!=nullptr){
			Guns[j]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));		// Attach each "Guns[j]" to the GetMesh(), aka the mesh of this cpp file, itc the ShooterCharacter. KeepRelativeTransform means we are keeping the location of the actor being spawned relative to the GetMesh to be constant. Otherwise, the other option is "KeepWorldTransform" which is keeping the location of the actor being spawned constand to the world, i.e the actor stays at the same spawn point in the world
			Guns[j]->SetOwner(this);	// setting the gun's owner to be the ShooterCharacter. Such that when we call 'getowner' in the gun.cpp, it means that we are calling the owner of the gun and that is this ShooterCharacter. 
			if(j != i){			//if j is not the i(activeindex by the WeaponSwitch() below). i is being changed by the mouse wheel (coz we set the BindAction to the mouse wheel and it changed as we move the mouse wheel), changing the mouse wheel will change the i value following the number of arrays index (see the "ChangeWeapon() function below for more detail").
			Guns[j]->SetActorHiddenInGame(true);	//(Hide the Actor)
			}
		}
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsAmmoReceived == true){
		AmmoReceived();
		bIsAmmoReceived=false;
		UGameplayStatics::SpawnSoundAttached(ReloadAmmoSound, Gun->Mesh, TEXT("MuzzleFlashSocket"));
	}
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
	PlayerInputComponent->BindAction("Weapon", IE_Pressed, this, &AShooterCharacter::ChangeWeapon);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);		//setting the damageapplied value to be whichever smaller between DamageToApply or Health.
	Health-=DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health %f"), Health);

	// if(Health == 0){
	// 	Dead = true;
	// }
	if(IsDead()){					// control what happen when the pawn dead
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();		//getting the hold of our game mode
		if(GameMode != nullptr){
			GameMode -> PawnKilled(this);		//pass in this (ShooterCharacter) to the PawnKilled function in SimpleShooterGameModeBase (in which we store in the 'GameMode' variable)
		}
		DetachFromControllerPendingDestroy();		//take the control out of this character (Both AI and player, depending on who's in control of that pawn so if enemy dead then its the AI). The pawn will no longer be able to move and shoot, etc.
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);												//switch off the capsule collision
	}													
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

float AShooterCharacter::GetHealthPercent() const	
{
	return Health/MaxHealth;
}


void AShooterCharacter::Shoot()
{
	if(Ammo>0){
		Gun->PullTrigger();
		Ammo--;
	}
	else{
		UGameplayStatics::SpawnSoundAttached(OutOfAmmoSound, Gun->Mesh, TEXT("MuzzleFlashSocket"));
	}
}
int AShooterCharacter::GetAmmoQuantity() const
{
	return Ammo;
}

void AShooterCharacter::AmmoReceived()
{
	Ammo=MaxAmmo;
}

bool AShooterCharacter::IsDead() const
{
	return Health<= 0;						//this is the same as if we return true when Health<0. So save some space noneed to make if statement when health<=0
}

void AShooterCharacter::ChangeWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Weapon Changed!"));

	// Gun = GetWorld()->SpawnActor<AGun>(GunClasses[i]);		//spawn the gun, if the location and rotation is not specified, it will just spawn at global coordinate 0,0,0
	// Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));		// Attach the "Gun" to the GetMesh(), aka the mesh of this cpp file, itc the ShooterCharacter. KeepRelativeTransform means we are keeping the location of the actor being spawned relative to the GetMesh to be constant. Otherwise, the other option is "KeepWorldTransform" which is keeping the location of the actor being spawned constand to the world, i.e the actor stays at the same spawn point in the world
	
	// GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);		//hide the weapon_r skeletalmesh (the weapon bawaan by the wraith, open 'wraith' and search for weapon_r @ the skeleton tree and ull now what i mean). We need to hide this bcs we're attaching a new gun mesh (which is defined by the 'Gun' variable above) if you see Exxx its an Enum and need to be followed by double colon (Exxx::)
	// Gun->SetOwner(this);	// setting the gun's owner to be the ShooterCharacter. Such that when we call 'getowner' in the gun.cpp, it means that we are calling the owner of the gun and that is this ShooterCharacter. 
	// Guns[i]->HandleDestruction();
	if(i>=GunClasses.Num()-1){		//if i gets larger than the indexing number (we -1 so that it will be the same as the indexing number and NOT the member quantity, coz i is the indexing number!). Hence if total member of an array is 3, -1 will make it 2, which is same as the indexing number! (0, 1, '2') eventhought the quantity is set to 3, we are more interested in the indexing number since i itself is an indexing number! (make it consistent...)
		i=0;						//need to set to 0! coz if only i--, it will only decrement once since -1 can already make it <GunClasses.Num()-1! so can't make it return to 0. Need other logic tho... So if GunClasses.Num() is 3, it will only increment between 3 3 3 since 2 will not go go 1 since 2 is already <GunClasses.Num() which we set to 3. Need other logic!
	}
	else {							//else  if i is not larger than the indexing number
		i++;
	}
	UE_LOG(LogTemp, Warning, TEXT("i=%i!"), i);
	int arraynum = GunClasses.Num();				//array num correspond to the total membeer in an array but not by the indexing number(which starting from 0)! So if there are 2 members in an array (0 and 1), Array.Num() will count it as 2 and not 1! eventhough the index is 0 and 1 it count the quantity! not the indexing number (so 2, not 1).
	UE_LOG(LogTemp, Warning, TEXT("array num=%i!"), arraynum);
}

//Fill out your copyright notice in the Description page of Project Settings.
 
// #include "SimpleShooterGameModeBase.h"
// #include "Components/CapsuleComponent.h"
// #include "ShooterCharacter.h"
// #include "Gun.h"
 
// // Sets default values
// AShooterCharacter::AShooterCharacter()
// {
//  	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
// 	PrimaryActorTick.bCanEverTick = true;
 
// }
 
// // Called when the game starts or when spawned
// void AShooterCharacter::BeginPlay()
// {
// 	Super::BeginPlay();
 
// 	Health = MaxHealth;
 
// 	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
// 	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
// 	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("WeaponSocket")));
// 	Gun->SetOwner(this); 
// 	int i = 0;
// 	for (AGun* gun : Guns)
// 	{
// 		if (gun != nullptr)
// 		{
// 			Gun->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
// 			gun = GetWorld()->SpawnActor<AGun>(GunClasses[i]);
// 			gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("WeaponSocket")));
// 			gun->SetOwner(this);
// 			i++;
// 		}
// 		else return;
// 	}
// }
 
// // Called every frame
// void AShooterCharacter::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
 
// }
 
// bool AShooterCharacter::IsDead() const
// {
// 	if (Health == 0) return true;
// 	else return false;
// }
 
// // Called to bind functionality to input
// void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);
// 	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
// 	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
// 	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
// 	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
// 	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Jump);
// 	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
 
// }
 
// void AShooterCharacter::MoveForward(float AxisValue)
// {
// 	AddMovementInput(GetActorForwardVector() * AxisValue);
// }
// void AShooterCharacter::MoveRight(float AxisValue)
// {
// 	AddMovementInput(GetActorRightVector() * AxisValue);
// }

// void AShooterCharacter::Shoot()
// {
// 	Gun->PullTrigger();
// }
 
// float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
// {
// 	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
// 	DamageToApply = FMath::Min(Health, DamageToApply);
// 	Health -= DamageToApply;
// 	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health)
 
// 	if(IsDead())
// 	{
// 		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
// 		if (GameMode != nullptr)
// 		{
// 			GameMode->PawnKilled(this);
// 		}
// 		DetachFromControllerPendingDestroy();
// 		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
// 	}
 
// 	return DamageToApply;
// }
 
// float AShooterCharacter::GetHealthPercent() const
// {
// 	return Health/MaxHealth;
// }
 
// void AShooterCharacter::AddGun(AGun* gun)
// {
// 	Guns.Add(gun);
// 	UE_LOG(LogTemp, Warning, TEXT("Added"))
// }
