// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzles/Plate.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyActor.h"

// Sets default values
APlate::APlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	Plate = CreateDefaultSubobject<UStaticMeshComponent>("Plate");
	Plate->SetupAttachment(SceneComponent);

}

// Called when the game starts or when spawned
void APlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APlate::IsPushedButton()
{
	return ReadyToMove();
}

bool APlate::ReadyToMove()
{

	TArray<AActor*>FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyActor::StaticClass(), FoundActors);

	for (auto Actor : FoundActors) {
		
		auto ButtonActor = Cast<AMyActor>(Actor);
	
		if (ButtonActor->GetIndex() == 0 && !ButtonActor->IsPushed()) {
			return false;
		}
	}

	return true;
}

