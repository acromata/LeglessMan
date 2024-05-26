// Fill out your copyright notice in the Description page of Project Settings.


#include "LeglessMan/Pickups/Legs/LegPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ALegPickup::ALegPickup()
{
	// Sphere collider
	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	Collision->SetupAttachment(RootComponent);
	Collision->SetSphereRadius(50.f);

	// Mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Collision);
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
		Destroy();
	}
}

