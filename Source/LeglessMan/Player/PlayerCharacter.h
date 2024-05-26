// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class LEGLESSMAN_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* InteractOverlap;

protected:

	// Input
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* InteractAction;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// Movement
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();

	// Sprinting
	void StartSprint();
	void EndSprint();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprinting")
	float WalkSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sprinting")
	float RunSpeed;

	// Interact
	void Interact();

	UFUNCTION()
	void OnInteractOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnInteractOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	int32 MaxLegsInInventory;
	UPROPERTY(BlueprintReadWrite)
	int32 NumOfLegsCollected;

	TArray<AActor*> InteractActorsInRange;

	// Dialogue
	UPROPERTY(BlueprintReadOnly)
	class ANPCCharacter* NPCTalkingTo;

public:

	// Inventory
	bool AddLegToInventory();

	UFUNCTION(BlueprintCallable)
	void RemoveNumOfLegsCollected(int32 Amount) { NumOfLegsCollected -= Amount; }

	// Dialogue
	UFUNCTION(BlueprintImplementableEvent)
	void AddNewDialogueOption(const FString& DialogueResponseText, int32 DialogeResponseIndex);

	void SetNPCTalkingTo(ANPCCharacter* NPC) { NPCTalkingTo = NPC; }

};
