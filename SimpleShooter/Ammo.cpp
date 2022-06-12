// Fill out your copyright notice in the Description page of Project Settings.

#include "Ammo.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo"));
	RootComponent = AmmoMesh;	//RootComponent is already part of the actor class, if you ctrl+click on it it will open the actor.h file showing that it is declared with the USceneComponent data type.

}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
	Super::BeginPlay();
	AmmoMesh->OnComponentHit.AddDynamic(this, &AAmmo::OnHit);		// call the 'OnHit' function on &AAmmo when the actor is being hit. Wo this line of code, the  OnHit function will never be called thus, the function when the actor is hit will never be executed
}
void AAmmo::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)		//a function to tell what to do when something (an 'Other Actor') hit something ()
{
	if(AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(OtherActor))		//check if the one hiiting the ammo actor is the player(shootercharacter) and not the AI
	{
		ShooterCharacter->bIsAmmoReceived = true;
		Destroy();
	}
}


// Called every frame
void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

