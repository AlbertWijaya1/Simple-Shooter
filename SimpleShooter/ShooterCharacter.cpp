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

/*The way how we do the array is that we are storing all Guns we set in the GunClasses inside a variable array (means an array of variable) called 'Guns', so Guns[0] will store GunClasses[0], Guns[1] will store GunClassess[1] and so on.
We make a for loop (for j) so that we no need to do this manually. If 2 weapon OK! but what if there's 100 weapon? setting for loop is much better! it'll store all the respective GunClasses[x] to its Guns[x].
So with now all the variable Guns[x] being set,anything we want to do with the gun can be done to the Guns[x], e.g. Hide => Guns[0]->SetActorHiddenInGame(true), and so on.*/



/*Guns.Emplace(GetWorld()->SpawnActor<AGun>(GunClasses[j])); will add member to the 'Guns' array. The member will going to be actors spawn with its respective GunClasses[j]. Since the for loop will iterate in order, the Guns[] will also be filled in order!
e.g. Guns[0] = GetWorld()->SpawnActor<AGun>(GunClasses[0]), Guns[1] = GetWorld()->SpawnActor<AGun>(GunClasses[1]), etc. NB: we set the member of the GunClasses manually in the BP_ShooterCharacter.
We need to do this to specify which gun we want to refer to (itc which gun to be spawned), and the reason why we can choose this in the BP_ShooterCharacter is bcs we set the class of the GunClasses array to be a TSubClassOf. This Allows us to have the dragdown list option to selfpick the BP that inherits the class we desire that suits the needs  */

/*kalau array go out of bounds, pelan2 baca aja! masukin 0 gimana, masukin 1 gimana. 
gabisa yang atas baru [0] tapi bawahnya uda [1]! ya out of bounds! (ingat for loop mulai dari 0, so if baru mulai dari [0], bawah gada yg boleh lebih dari itu! ([>0]))
This is what happen w me b4,  use for loops, first kan [0] (j=0) but I uda set aja [1] di bawah, ya out of bound la!
intinya masukin aja manual pelan2 n dibaca kira2 possible ga?*/

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

	UE_LOG(LogTemp, Warning, TEXT("Gunclass Num = %i!"), GunClasses.Num());
	UE_LOG(LogTemp, Warning, TEXT("Guns Num = %i!"), Guns.Num());

	for(j; j<GunClasses.Num();j++){
		Guns.Emplace(GetWorld()->SpawnActor<AGun>(GunClasses[j]));		//emplacing means adding the array wo creating temporary thingy, if use 'add' it'll create the temporary thingy. and here, we are adding the guns in the GunClasses to the Guns array. 'SpawnActor' means we are Spawning the gun, if the location and rotation is not specified, it will just spawn at global coordinate 0,0,0 (we fill in the location and rotation at BasePawn.cpp @ ToonTanks lecture when we want to spawn the projectile)
		if(Guns[j]!=nullptr){
			Guns[j]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));		// Attach each "Guns[j]" to the GetMesh(), aka the mesh of this cpp file, itc the ShooterCharacter. KeepRelativeTransform means we are keeping the location of the actor being spawned relative to the GetMesh to be constant. Otherwise, the other option is "KeepWorldTransform" which is keeping the location of the actor being spawned constand to the world, i.e the actor stays at the same spawn point in the world
			Guns[j]->SetOwner(this);	// setting the gun's owner to be the ShooterCharacter. Such that when we call 'getowner' in the gun.cpp, it means that we are calling the owner of the gun and that is this ShooterCharacter. 
			Guns[0]->SetActorHiddenInGame(true);			//hide the first array member of Guns[j] where we emplace with GunClasses that where we set manually the gun in the BP_ShooterCharacter due to the TSubClassOf
			Guns[0]->SetActorEnableCollision(false);		//turn off the collision the first array member of Guns[j] where we emplace with GunClasses that where we set manually the gun in the BP_ShooterCharacter due to the TSubClassOf
			Guns[0]->SetActorTickEnabled(false);			//Turn tick system off for the first array member of Guns[j] where we emplace with GunClasses that where we set manually the gun in the BP_ShooterCharacter due to the TSubClassOf

			// if(j != i){			//if j is not the i(activeindex by the WeaponSwitch() below). i is being changed by the mouse wheel (coz we set the BindAction to the mouse wheel and it changed as we move the mouse wheel), changing the mouse wheel will change the i value following the number of arrays index (see the "ChangeWeapon() function below for more detail").
				// Guns[i]->SetActorHiddenInGame(true);	//(Hide the Actor)
			// }
			// UE_LOG(LogTemp, Warning, TEXT("Gun Num = %i!"), Guns.Num());
		}
	}

	// UE_LOG(LogTemp, Warning, TEXT("Guns Num = %i!"), Guns.Num());
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsAmmoReceived == true){
		AmmoReceived();
		bIsAmmoReceived=false;
		UGameplayStatics::SpawnSoundAttached(ReloadAmmoSound, Guns[i]->Mesh, TEXT("MuzzleFlashSocket"));

	}
	UE_LOG(LogTemp, Warning, TEXT("j = %i!"), j);
	UE_LOG(LogTemp, Warning, TEXT("i = %i!"), i);
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
	return Health/MaxHealth;			// bcs we are showing the health in a form of progression bar and to show how much progress (in this case how much health is remaining), we need to make it in a form of fraction (aka Health/MaxHealth = how much health remaining compare to the maxhealth)
}


void AShooterCharacter::Shoot()
{
	if(Ammo>0){
		Guns[i]->PullTrigger();
		// Ammo--;
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
	// UE_LOG(LogTemp, Warning, TEXT("array num=%i!"), arraynum);
	// Guns[i]->SetActorHiddenInGame(true);	//(Hide the Actor)
	// if(i==ActiveGunIndex){
		// Gun->SetActorHiddenInGame(true);				// hide the 'Gun' but since we have change the 'Gun' to Guns[j], we no longer need this and it will crash if we did this since we haven't define 'Gun' anywhere and that we have commented that section out of the code.
		Guns[!i]->SetActorHiddenInGame(true);			//set the Guns[not{thus the !} active index] to be hidden
		Guns[i]->SetActorHiddenInGame(false);
	// }


	// Guns.Emplace(GetWorld()->SpawnActor<AGun>(GunClasses[0]));
	// Guns[0]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	// Guns[0]->SetOwner(this);

	// Guns.Emplace(GetWorld()->SpawnActor<AGun>(GunClasses[1]));
	// Guns[1]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	// Guns[1]->SetOwner(this);



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
