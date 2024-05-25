// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LeglessMan/Interfaces/Interact/InteractInterface.h"
#include "LeglessMan/Data/Dialogue/DialogueTable.h"
#include "NPCCharacter.generated.h"

UCLASS()
class LEGLESSMAN_API ANPCCharacter : public ACharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	virtual void Interact(APlayerCharacter* Player) override;

	UFUNCTION(BlueprintImplementableEvent)
	void PreDialogueStart();
	UFUNCTION(BlueprintImplementableEvent)
	void EndDialogue();
	UFUNCTION(BlueprintCallable)
	void OnOptionSelected(APlayerCharacter* Player);

	void ShowDialogueOptions(APlayerCharacter* Player);

	// Dialogue
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue")
	TArray<FDialogueData> DialogueData;

	UPROPERTY(BlueprintReadWrite)
	int32 DialogueStateIndex;
	UPROPERTY(BlueprintReadWrite)
	int32 DialogueIndexToRead;
	UPROPERTY(BlueprintReadOnly)
	FString CurrentDialogue;
	UPROPERTY(BlueprintReadOnly)
	bool bHasPlayerReadDialogue;
	UPROPERTY(BlueprintReadWrite)
	bool bIsShowingOptions;
};
