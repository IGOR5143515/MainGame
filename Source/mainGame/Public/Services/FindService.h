// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindService.generated.h"

/**
 * 
 */
UCLASS()
class MAINGAME_API UFindService : public UBTService
{
	GENERATED_BODY()
public:
	UFindService();
	

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Service")
	FBlackboardKeySelector KeySelector;


};
