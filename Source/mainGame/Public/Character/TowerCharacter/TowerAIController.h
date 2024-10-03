// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/MyAIController.h"
#include "TowerAIController.generated.h"

class AProjectile;

UCLASS()
class MAINGAME_API ATowerAIController : public AMyAIController
{
	GENERATED_BODY()

public:
	ATowerAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
protected:

	//UFUNCTION()
	//void OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus);
	
	AActor* CurrentTurget=nullptr;

	FName MuzzleName = "Muzzle";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AProjectile> ProjectileClass;

	bool CanFire=true;

	FTimerHandle TimerHandle;
	void Fire();
	void ResetFire() { CanFire = true; }

	AActor *FindCurrnetTarget();

};
