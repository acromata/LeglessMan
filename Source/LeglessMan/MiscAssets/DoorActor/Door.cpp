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
	}
	else
	{
		bIsOpen = true;
	}
}

void ADoor::OpenDoor(float DeltaTime)
{
	if (bIsOpen && !DoorMesh->GetRelativeLocation().IsNearlyZero())
	{
		DoorMesh->SetRelativeRotation(FMath::RInterpTo(GetActorRotation(), OpenRotation, DeltaTime, DoorOpenSpeed));
	}

}
