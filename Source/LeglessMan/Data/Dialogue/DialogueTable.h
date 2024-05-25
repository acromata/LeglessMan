// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DialogueTable.generated.h"


USTRUCT(BlueprintType)
struct LEGLESSMAN_API FDialogueData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, int32> DialogueResponses;
};
