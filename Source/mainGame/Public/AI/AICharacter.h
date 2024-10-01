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

	void TraceToTakeDamage();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AttackAndAnimation(AActor * Actor);
	FTimerHandle TimerHandle;

	bool StartAnimation = false;

	void ResetAnimation() { StartAnimation = false; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaivorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UAnimMontage* AnimMontage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UAnimMontage* DeathAnimMontage;
};
