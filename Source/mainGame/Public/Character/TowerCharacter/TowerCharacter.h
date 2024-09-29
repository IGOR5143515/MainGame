// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CubeCharacter.h"
#include "TowerCharacter.generated.h"

class UMyAIPerceptionComponent;

UCLASS()
class MAINGAME_API ATowerCharacter : public ACubeCharacter
{
	GENERATED_BODY()
public:
	bool IsDead=false;
public:
	ATowerCharacter();

	virtual void OnDeath()override;

	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult)override;
	

	


};
