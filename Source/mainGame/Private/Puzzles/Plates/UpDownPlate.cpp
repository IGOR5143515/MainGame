// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzles/Plates/UpDownPlate.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyActor.h"

bool AUpDownPlate::ReadyToMove()
{
	TArray<AActor*>FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyActor::StaticClass(), FoundActors);

	for (auto Actor : FoundActors) {

		auto ButtonActor = Cast<AMyActor>(Actor);

		if (ButtonActor->GetIndex() ==1 && !ButtonActor->IsPushed()) {
			return false;
		}
	}

	return true;
}
