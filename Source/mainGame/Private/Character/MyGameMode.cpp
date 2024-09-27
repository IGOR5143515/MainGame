// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyGameMode.h"
#include "Character/CubeCharacter.h"
#include "Character/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Character/TowerCharacter/TowerCharacter.h"
#include "AI/AICharacter.h"
#include "AI/MyAIController.h"


AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = ACubeCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();

}

UClass* AMyGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AMyAIController>())
		return AIPawnClass;
	else
		return Super::GetDefaultPawnClassForController_Implementation(InController);
}

bool AMyGameMode::GameOver()
{
	bool temp=false;
	TArray<AActor*> TowersArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATowerCharacter::StaticClass(), TowersArray);

	for (auto& x : TowersArray) {

		ATowerCharacter* Tower = Cast<ATowerCharacter>(x);
		
		if (Tower->IsDead)
			temp = true;
		else return false;

	}
	return temp;

}

void AMyGameMode::Tick(float DeltaSeconds)
{
	if (GameOver())
		UE_LOG(LogTemp, Error, TEXT("Destroy all towers!!!"));
	

}

void AMyGameMode::SpawnBots(FVector Location, FRotator Rotation)
{


	FActorSpawnParameters SpawnParametrs;
	SpawnParametrs.SpawnCollisionHandlingOverride= ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto AIController = GetWorld()->SpawnActor<AMyAIController>(BotClass, Location, Rotation, SpawnParametrs);
	RestartPlayer(AIController);


}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();
	SpawnBots(FVector(0, 0, 0), FRotator(0, 0, 0));

}
