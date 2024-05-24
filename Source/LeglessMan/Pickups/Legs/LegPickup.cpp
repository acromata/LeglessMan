// Fill out your copyright notice in the Description page of Project Settings.


#include "LeglessMan/Pickups/Legs/LegPickup.h"

// Sets default values
ALegPickup::ALegPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALegPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALegPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALegPickup::Interact(APlayerCharacter* Player)
{
	if (Player->AddLegToInventory())
	{
		Destroy();
	}
}

