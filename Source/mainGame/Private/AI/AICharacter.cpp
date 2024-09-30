// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"
#include "AI/MyAIController.h"
#include "Components/HealthComponent.h"
#include "AI/MyAIPerceptionComponent.h"
#include "Components/CapsuleComponent.h"

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
	auto controll =Cast<AMyAIController>(GetController());
	if (!controll)return;
	controll->Perception->SetActive(false);

	SetActorEnableCollision(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetLifeSpan(0.1f);
}

void AAICharacter::OnTakeAnyDamageHandleAI(AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{


	HealthComponent->TakeDamage(25);

	if (HealthComponent->IsDead())
		HealthComponent->OnDeathDelegate.Broadcast();

}
