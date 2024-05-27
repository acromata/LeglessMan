#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeglessMan/Interfaces/Interact/InteractInterface.h"
#include "Door.generated.h"

UCLASS()
class LEGLESSMAN_API ADoor : public AActor, public IInteractInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* DoorMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* FrameMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* LockMesh;

	
public:
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void Interact(APlayerCharacter* Player) override;

	void OpenDoor(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Values")
	bool bIsLocked;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Values")
	FRotator OpenRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Values")
	float DoorOpenSpeed;

	bool bIsOpen;
};
