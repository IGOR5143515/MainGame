// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class UAIPerceptionComponent;

UCLASS()
class MAINGAME_API AMyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMyAIController();

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* Perception;



};
