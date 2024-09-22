// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"
#include "AI/MyAIController.h"
#include "Components/HealthComponent.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AMyAIController::StaticClass();

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HelathComponent");

}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	HealthComponent->OnDeathDelegate.AddUObject(this, &AAICharacter::OnDeathAI);
	OnTakeAnyDamage.AddDynamic(this, &AAICharacter::OnTakeAnyDamageHandleAI);

}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AAICharacter::OnDeathAI()
{
	SetLifeSpan(1.0f);
}

void AAICharacter::OnTakeAnyDamageHandleAI(AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (HealthComponent->GetHealth() <= 0)
		HealthComponent->OnDeathDelegate.Broadcast();

	HealthComponent->TakeDamage(25);


}
