// Fill out your copyright notice in the Description page of Project Settings.


#include "LeglessMan/Pickups/Legs/LegPickup.h"


// Sets default values
ALegPickup::ALegPickup()
{

}

// Called when the game starts or when spawned
void ALegPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALegPickup::Interact(APlayerCharacter* Player)
{
	if (Player->AddLegToInventory())
	{
		OnPickup(Player);
		Destroy();
	}
}

