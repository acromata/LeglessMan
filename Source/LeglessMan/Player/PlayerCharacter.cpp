// Fill out your copyright notice in the Description page of Project Settings.


#include "../Player/PlayerCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LeglessMan/Interfaces/Interact/InteractInterface.h"
#include "Components/SphereComponent.h"
#include "LeglessMan/NPCs/NPCCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	// Interact Overlap
	InteractOverlap = CreateDefaultSubobject<USphereComponent>("InteractOverlap");
	InteractOverlap->SetupAttachment(RootComponent);
	InteractOverlap->SetSphereRadius(300.f);

	// Sprinting
	WalkSpeed = 400.f;
	RunSpeed = 800.f;

	MaxLegsInInventory = 1;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Interact overlap bindings
	InteractOverlap->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnInteractOverlapBegin);
	InteractOverlap->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnInteractOverlapEnd);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	// Input actions
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);

		Input->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StartSprint);
		Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::EndSprint);

		Input->BindAction(InteractAction, ETriggerEvent::Completed, this, &APlayerCharacter::Interact);
	}
}

#pragma region Movement

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void APlayerCharacter::Jump()
{
	ACharacter::Jump();
}

#pragma endregion

#pragma region Sprint

void APlayerCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void APlayerCharacter::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

#pragma endregion

#pragma region Interact

void APlayerCharacter::Interact()
{
	if (InteractActorsInRange.IsValidIndex(0) && IsValid(InteractActorsInRange[0]))
	{
		IInteractInterface* InteractActor = Cast<IInteractInterface>(InteractActorsInRange[0]);
		if (InteractActor)
		{
			InteractActor->Interact(this);
		}
	}

}

void APlayerCharacter::OnInteractOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IInteractInterface* InteractActor = Cast<IInteractInterface>(OtherActor);
	if (InteractActor && !InteractActorsInRange.Contains(OtherActor))
	{
		InteractActorsInRange.Add(OtherActor);
	}
}

void APlayerCharacter::OnInteractOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (InteractActorsInRange.Contains(OtherActor))
	{
		InteractActorsInRange.RemoveSingle(OtherActor);

		if (NPCTalkingTo == OtherActor)
		{
			NPCTalkingTo = nullptr;
		}
	}
}

bool APlayerCharacter::AddLegToInventory()
{
	if (NumOfLegsCollected < MaxLegsInInventory)
	{
		NumOfLegsCollected++;
		return true;
	}
	else
	{
		return false;
	}
}

#pragma endregion