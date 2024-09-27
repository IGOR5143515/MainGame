// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TowerCharacter/TowerCharacter.h"
#include "Character/TowerCharacter/TowerAIController.h"
#include "Engine/DamageEvents.h"

ATowerCharacter::ATowerCharacter() :Super()
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ATowerAIController::StaticClass();
}

void ATowerCharacter::OnDeath()
{
	Super::OnDeath();
	IsDead = true;
}



void ATowerCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	Super::TakeDamage(10.0f, FDamageEvent(), Controller, OtherActor);

	
}






