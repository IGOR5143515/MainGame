// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTask.h"
#include "Kismet/GameplayStatics.h"
#include "Character/CubeCharacter.h"
#include "AI/MyAIController.h"
#include "AI/AICharacter.h"
UDamageTask::UDamageTask()
{
	NodeName = "FireService";
}

EBTNodeResult::Type UDamageTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (!Controller)return EBTNodeResult::Failed;

	APawn* Pawn = Controller->GetPawn();
	if (!Pawn)return EBTNodeResult::Failed;

	AAICharacter* AICharacter = Cast<AAICharacter>(Pawn);
	if (!AICharacter)return EBTNodeResult::Failed;

	ACubeCharacter * character= Cast<ACubeCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), ACubeCharacter::StaticClass()));
	if (!character)return EBTNodeResult::Failed;

	if (character->IsOverlapCube) {
		UE_LOG(LogTemp, Error, TEXT("Take Damage AI"));
	}

	return EBTNodeResult::Succeeded;
}
