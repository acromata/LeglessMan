// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeglessMan/Interfaces/Interact/InteractInterface.h"
#include "Pickup.generated.h"

UCLASS()
class LEGLESSMAN_API APickup : public AActor, public IInteractInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	virtual void Interact(APlayerCharacter* Player) override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPickup(APlayerCharacter* Player);

};
