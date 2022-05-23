// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
    Mesh =  CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    Mesh -> SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	// UE_LOG(LogTemp, Warning, TEXT("U've been shot"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));		//attach the particle emiiter to the  mesh of the muzzle flash socket (Open the rifle mesh and see the skeleton tree to get the name of the socket you want to attach it to! itc its 'MuzzleFlashSocket', if there isn't any, you can create one by right clicking and 'Add Socket')
	
	APawn* OwnerPawn = Cast <APawn>(GetOwner()); // this is similar to setting OwnerPawn = GetOwner(), but since APawn is the child of AActor, we need casting!

	if(OwnerPawn == nullptr){return;}
	AController* OwnerController = OwnerPawn->GetController();
	if(OwnerController == nullptr) return;

	FVector Location;												//this doesn't mean anything yet! just a declaration of an empty variable under the data type 'FVector', later we will call the 'GetPlayerViewPoint()' function to overwrite this empty variable into something more meaningful, itc getting the data of the live location of the player to this 'Location' variable.
	FRotator Rotation;												//this doesn't mean anything yet! just a declaration of an empty variable under the data type 'FRotator', later we will call the 'GetPlayerViewPoint()' function to overwrite this empty variable into something more meaningful, itc getting the data of the live location of the player to this 'Rotation' variable.
	OwnerController->GetPlayerViewPoint(Location, Rotation);		//since location and rotation is an out parameter, they both can now be overwritten by sth else. In this case, we want to overwrite it with the live location and rotation of the player, and we can achieve that by using 'GetPlayerViewPoint()'. We placed the outparameter that we want to overwrite with the live location of the player, itc to the 'location' and 'rotation'. Otherwise, 'location' and 'rotation' will only be an empty variable since we are not assigning the variable into anything! we only declare it at the top: FVector Location, FRotator Rotation. By doing GetPlayerViewPoint(Location, Rotation), we are overwriting that location and rotation variable into the live location and rotation of the player, and this can be done bcs GetPlayerViewPoint takes in an out parameter (can confirm by F12-ing the function)! if it's not an out parameter, we will not be able to overwrite the parameter that has been sub into the function. That is why we have fun(&A) so that A can be changed to whatever the fun wants A to be changed into.
	// DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);		//draw the camera  at 'Location and 'Rotation' and set the persistent line to 'true'.

	FVector End = Location + Rotation.Vector()*MaxRange;			//the max range will determine how far can the bullet travels! a large number means that we can shoot really2 far and that the bullet will be able to travel quite a distance and hit the target despite being really far from the target we want to hit.
	FHitResult  HitResult;											//this doesn't mean anything yet! just a declaration of an empty variable under the data type 'HitResult', later we will call the 'LineTraceSingleByChannel()' function to overwrite this empty variable into something more meaningful, itc getting the data of the linetrace (objectbeinghitbythecursor) to this HitResult varialbe.
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());	//if theres no intelllisece poping out, use the unreal engine documentation to know what parameter does the function need to be filled in. Get Owner at the end of the parameter means that we are ignoring ourselves at the "LineTraceSingleByObjectType" aka we are ignoring the player so that it doesn't count as being hit, otherwise the bullet hitting the player will count as hit and if we place the bullets to close to the player, it will count as hit! (can self damage perhaps?)
	GetWorld()->LineTraceSingleByChannel(
		HitResult,																		//The object being hit
		Location,
		End,
		ECollisionChannel::ECC_GameTraceChannel1,										//if you go to ProjectSettings>Engine>Collision, you can see that we have set a new Trace Channel named 'Bullet' and if you open C:\Users\alber\OneDrive\Documents\Unreal Projects\Simple Shooter\SimpleShooter\Config\DefaultEngine.ini, and search for "Bullet" you can see that it is being assign to 'ECC_GameTraceChannel1'. In this Trace Channel, we can set what the object we want to collide with and what we don't want to collide with the trace channel we set, itc its the 'Bullet', provided that we are using the LinTraceByChannel function, which we are... If we are using the LineTraceByObject function it won't work! If a datatype is an Exxx, meaning that it is an ENum! and we need to do "Exxx::"
		TraceParams																		//anything you want to ignore? itc yes! we want to ignore the Playeritself aka GetOwner() so that we are not having a 'self-hit'.
	);
	// DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 20, FColor::Red, true);			//can also do HitResult.Location (no "()") and it will do the same thing! since we want the location of where the bullet hits, it will be the same as HitResult.ImpactPoint
	FVector ShotDirection = -Rotation.Vector();
	UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, HitResult.Location, Rotation.Vector().Rotation());	//We put this right after we destroy the actor such coz it just doesn't make any sense to spawn the effects only right after the actor is destroyed. There are 3 options to fill in the parameter SpawnEmitterAtLocation(), hover over and click on the down arrow button to know what it is. The one we're using SpawnEmitterAtLocation(World context object, Particle system (we define this in the header file by the UparticleSystem class), Location, Rotation)
	AActor* HitActor = HitResult.GetActor();
	if(HitActor!=nullptr){
		FPointDamageEvent DamageEvent (Damage, HitResult, Rotation.Vector(), nullptr);		//FPointDamageEvent var(DamageQuantity, the object being hit (FHitResult DataType),ShotDirection (Which direction the shot is coming from?), DamageType(poison damage, burn damage, etc) pass null if none)
		HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);					//TakeDamage(DamageAmount, DamageEvent which provides more infomration to the damage that happen, Instigator: who is the controller responsible for causing the damage, DamageCauser: The actor causing the damage, can be a gun, a projectile that expolided, a rock landed on you, itc its the gun that shot u that is going to be responsible (not the controller! controller causing the damage is the instigator)).
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

