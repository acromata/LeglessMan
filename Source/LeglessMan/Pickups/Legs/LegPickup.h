// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LeglessMan/Pickups/Pickup.h"
#include "LegPickup.generated.h"

UCLASS()
class LEGLESSMAN_API ALegPickup : public APickup
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALegPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	virtual void Interact(APlayerCharacter* Player) override;
};
