// Fill out your copyright notice in the Description page of Project Settings.


#include "LeglessMan/Pickups/Pickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickup::APickup()
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
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickup::Interact(APlayerCharacter* Player)
{
	OnPickup(Player);
}

