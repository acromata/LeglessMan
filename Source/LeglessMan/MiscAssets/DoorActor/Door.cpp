#include "LeglessMan/MiscAssets/DoorActor/Door.h"

// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Components
	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>("Frame");
	FrameMesh->SetupAttachment(RootComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	DoorMesh->SetupAttachment(FrameMesh);

	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>("Lock");
	LockMesh->SetupAttachment(FrameMesh);

	LockShakeAmplitude = 5.f;
	LockShakeFrequency = 1.f;
	LockShakeTime = 1.f;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	LockMesh->SetVisibility(bIsLocked);
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OpenDoor(DeltaTime);

	ShakeLock(DeltaTime);
}

void ADoor::Interact(APlayerCharacter* Player)
{
	if (bIsLocked)
	{
		if (Player->HasKeyInInventory())
		{
			Player->RemoveKeyFromInventory();
			bIsLocked = false;
			LockMesh->SetVisibility(false);
		}
		else
		{
			RunningTime = 0;
			LockMesh->SetRelativeRotation(FRotator(0));

			bShouldShakeLock = true;
		}
	}
	else
	{
		if (bIsOpen)
		{
			TargetRotation = FRotator(0);
			bIsOpen = false;
		}
		else
		{
			TargetRotation = FRotator(OpenRotation);
			bIsOpen = true;
		}
	}
}

void ADoor::OpenDoor(float DeltaTime)
{
	DoorMesh->SetRelativeRotation(FMath::RInterpTo(DoorMesh->GetRelativeRotation(), TargetRotation, DeltaTime, DoorOpenSpeed));
}

void ADoor::ShakeLock(float DeltaTime)
{
	if (bShouldShakeLock)
	{
		RunningTime += DeltaTime;

		float ShakeAmount = FMath::Sin(RunningTime * LockShakeFrequency * 2.0f * PI) * LockShakeAmplitude;

		FRotator NewRotation = LockMesh->GetRelativeRotation();
		NewRotation.Pitch += ShakeAmount;
		LockMesh->SetRelativeRotation(NewRotation);

		if (RunningTime >= LockShakeTime)
		{
			bShouldShakeLock = false;
			RunningTime = 0;
			LockMesh->SetRelativeRotation(FRotator(0));
		}
	}
}
