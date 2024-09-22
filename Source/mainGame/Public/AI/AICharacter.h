// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

class UBehaviorTree;
class UHealthComponent;
UCLASS()
class MAINGAME_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

	UFUNCTION()
	void OnDeathAI();

	UFUNCTION()
	void OnTakeAnyDamageHandleAI(AActor* DamagedActor,
		float Damage,
		const UDamageType*
		DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaivorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UHealthComponent* HealthComponent;


};
