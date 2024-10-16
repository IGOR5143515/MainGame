// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyGameMode.h"
#include "Character/CubeCharacter.h"
#include "Character/MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Character/TowerCharacter/TowerCharacter.h"
#include "AI/AICharacter.h"
#include "AI/MyAIController.h"
#include "Engine/TargetPoint.h"


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
	//bool temp=false;
	//TArray<AActor*> TowersArray;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATowerCharacter::StaticClass(), TowersArray);

	//for (auto& x : TowersArray) {

	//	ATowerCharacter* Tower = Cast<ATowerCharacter>(x);
	//	
	//	if (Tower->IsDead)
	//		temp = true;
	//	else return false;

	//}
	//return temp;

	 auto Trone =Cast<ATowerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), TronClass));
	 if (!Trone) return false;

	 if (Trone->IsDead)
		 return true;
	 
	 return false;
}

void AMyGameMode::Tick(float DeltaSeconds)
{
	if (GameOver())
		UE_LOG(LogTemp, Error, TEXT("GAME OVER"));
}

void AMyGameMode::SpawnBots(FVector Location, FRotator Rotation)
{


	FActorSpawnParameters SpawnParametrs;
	SpawnParametrs.SpawnCollisionHandlingOverride= ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	if (!GetWorld())return;

	AAICharacter* AICharacter = GetWorld()->SpawnActor<AAICharacter>(AIPawnClass, Location, Rotation, SpawnParametrs);

	if (AICharacter) {

		AMyAIController* AIController = GetWorld()->SpawnActor<AMyAIController>(MyControllerAI, Location, Rotation, SpawnParametrs);
		if (AIController)
			AIController->Possess(AICharacter);

	}

}

void AMyGameMode::StartGame()
{
	TArray<AActor*>TargetPointArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), TargetPointArray);

	NumberOfEnemies += 1;

	for (size_t i = 0; i < NumberOfEnemies; i++)
	{
		for (auto x : TargetPointArray)
			SpawnBots(x->GetActorLocation(), x->GetActorRotation()); 
	}

}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!GetWorld())return;

	StartGame();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyGameMode::StartGame, OneMinute, true);  // Spawn Enamies avery 60 seconds



}
