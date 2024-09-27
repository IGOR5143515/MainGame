// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/FindService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/MyAIPerceptionComponent.h"
#include"AIController.h"
#include "Perception/AISense_Sight.h"
#include "Character/CubeCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Character/TowerCharacter/TowerCharacter.h"


UFindService::UFindService()
{

	NodeName = "FindService";

}

void UFindService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if (!BlackBoard)return;

	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller)return;

	auto Pawn = Controller->GetPawn();
	if (!Pawn)return;

	ACubeCharacter* Character = Cast<ACubeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character)return;

	
	const auto PerceptionComponent = Cast<UMyAIPerceptionComponent>(Controller->GetComponentByClass(UMyAIPerceptionComponent::StaticClass()));
	if (!PerceptionComponent)return;

	TArray<AActor*>FindingActors;

	PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), 
		FindingActors);

	if (FindingActors.Num() == 0) return;
	float BestDistance = MAX_FLT;
	FVector TempDistance = Character->GetActorLocation();
	bool bFoundTarget = false;

	for (auto x : FindingActors) {

		if (x->IsA<ACubeCharacter>() || x->IsA<ATowerCharacter>()) {


			auto CurrentDistance = (x->GetActorLocation() - Pawn->GetActorLocation()).Size();

			if (CurrentDistance < BestDistance) {
				BestDistance = CurrentDistance;
				TempDistance = x->GetActorLocation();
				bFoundTarget = true;
			}
		}
		
	}
	if (bFoundTarget) {
	BlackBoard->SetValueAsVector(KeySelector.SelectedKeyName, TempDistance);
	}

	

}

