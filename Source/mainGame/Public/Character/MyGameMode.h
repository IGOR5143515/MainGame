// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

class AMyAIController;

UCLASS()
class MAINGAME_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
public:

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController)override;

	AMyGameMode();

	bool GameOver();

	virtual void Tick(float DeltaSeconds) override;

	void SpawnBots(FVector Location, FRotator Rotation);

	virtual void BeginPlay()override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AMyAIController> BotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<APawn> AIPawnClass;
	
};
