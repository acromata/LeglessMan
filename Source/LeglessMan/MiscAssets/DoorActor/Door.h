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
	void ShakeLock(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	bool bIsLocked;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	FRotator OpenRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	float DoorOpenSpeed;

	FRotator TargetRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lock")
	float LockShakeAmplitude;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lock")
	float LockShakeFrequency;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lock")
	float LockShakeTime;
	UPROPERTY(BlueprintReadOnly)
	bool bIsOpen;
	float RunningTime;

	bool bShouldShakeLock;
};
