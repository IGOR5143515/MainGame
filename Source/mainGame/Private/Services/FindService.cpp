// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/FindService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/MyAIPerceptionComponent.h"
#include"AIController.h"
#include "Perception/AISense_Sight.h"
#include "Character/CubeCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


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

	ACubeCharacter* Character = Cast<ACubeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!Character)return;

	
	const auto PerceptionComponent = Cast<UMyAIPerceptionComponent>(Controller->GetComponentByClass(UMyAIPerceptionComponent::StaticClass()));
	if (!PerceptionComponent)return;

	TArray<AActor*>FindingActors;

	PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), 
		FindingActors);

	for (auto x : FindingActors) {

		if (x->IsA<ACubeCharacter>()) {
			BlackBoard->SetValueAsVector(KeySelector.SelectedKeyName, Character->GetActorLocation());
		}

	}



	

}

