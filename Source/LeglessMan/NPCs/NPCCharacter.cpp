// Fill out your copyright notice in the Description page of Project Settings.


#include "LeglessMan/NPCs/NPCCharacter.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCCharacter::Interact(APlayerCharacter* Player)
{
	// Check if NPC has any special dialogue inside blueprint
	// If it does, the blueprint will change the DialogueStateIndex
	PreDialogueStart();

	if (DialogueData.IsValidIndex(DialogueStateIndex))
	{
		Player->SetNPCTalkingTo(this);

		if (!bHasPlayerReadDialogue)
		{
			if (DialogueData[DialogueStateIndex].DialogueText.IsValidIndex(DialogueIndexToRead))
			{
				// Get dialogue
				CurrentDialogue = DialogueData[DialogueStateIndex].DialogueText[DialogueIndexToRead];

				// Move to next dialogue on next input
				DialogueIndexToRead++;
			}
			else
			{
				// No more input, reset
				bHasPlayerReadDialogue = true;

				// Read last dialogue line on next input
				DialogueIndexToRead = DialogueData[DialogueStateIndex].DialogueText.Num() - 1;

				if (!DialogueData[DialogueStateIndex].DialogueResponses.IsEmpty())
				{
					ShowDialogueOptions(Player);
				}
				else
				{
					// Reset player NPC talking to
					Player->SetNPCTalkingTo(nullptr);
				}
			}
		}
		else
		{
			if (DialogueData[DialogueStateIndex].DialogueText.IsValidIndex(DialogueIndexToRead))
			{
				// Get dialogue
				CurrentDialogue = DialogueData[DialogueStateIndex].DialogueText[DialogueIndexToRead];

				// Move to next dialogue on next input
				DialogueIndexToRead++;
			}
			else
			{
				// Read last dialogue line on next input
				DialogueIndexToRead = DialogueData[DialogueStateIndex].DialogueText.Num() - 1;

				if (!DialogueData[DialogueStateIndex].DialogueResponses.IsEmpty())
				{
					ShowDialogueOptions(Player);
				}
				else
				{
					// Reset player NPC talking to
					Player->SetNPCTalkingTo(nullptr);
				}
			}
		}
	}
}

void ANPCCharacter::ShowDialogueOptions(APlayerCharacter* Player)
{
	if (!bIsShowingOptions)
	{
		for (TTuple<FString, int32> Response : DialogueData[DialogueStateIndex].DialogueResponses)
		{
			Player->AddNewDialogueOption(Response.Key, Response.Value);
		}

		bIsShowingOptions = true;
	}
}

void ANPCCharacter::OnOptionSelected(APlayerCharacter* Player)
{
	// Reset values
	bIsShowingOptions = false;

	if (DialogueStateIndex != -1)
	{
		// Reset values
		bHasPlayerReadDialogue = false;
		DialogueIndexToRead = 0;

		// Show next dialogue
		Interact(Player);
	}
	else
	{
		// Reset player NPC talking to
		Player->SetNPCTalkingTo(nullptr);
	}

}

