// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "AI/AICharacter.h"

AMyAIController::AMyAIController()
{


	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
	SetPerceptionComponent(*Perception);

}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (auto CharComponent = Cast<AAICharacter>(InPawn)) {

		RunBehaviorTree(CharComponent->BehaivorTree);
	}


}
