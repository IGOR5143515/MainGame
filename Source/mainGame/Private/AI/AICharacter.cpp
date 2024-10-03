// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"
#include "AI/MyAIController.h"
#include "Components/HealthComponent.h"
#include "AI/MyAIPerceptionComponent.h"
#include "Components/CapsuleComponent.h"
#include "Character/CubeCharacter.h"
#include "Character/TowerCharacter/TowerCharacter.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"



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
	TraceToTakeDamage();
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
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	SetLifeSpan(3.0f);
	PlayAnimMontage(DeathAnimMontage);
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

void AAICharacter::TraceToTakeDamage()
{
	if (!GetWorld())return;
	FVector Location = GetActorLocation();
	FVector Rotation= GetActorRotation().Vector();

	FVector TraceEnd = Location + (Rotation * 100);

	FCollisionQueryParams COQP;
	COQP.AddIgnoredActor(this);
	FCollisionResponseParams ColRes;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Location, TraceEnd,
		ECollisionChannel::ECC_Visibility, COQP);
	
	if (HitResult.bBlockingHit&&HitResult.GetActor()->IsA<ACubeCharacter>()) {
		if (!StartAnimation&&!HealthComponent->IsDead()) {
			StartAnimation = true;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAICharacter::ResetAnimation, 1.0f, false);

			AttackAndAnimation(HitResult.GetActor());
		}
			
	}
}

void AAICharacter::AttackAndAnimation(AActor* Actor)
{
	if (!GetWorld())return;

	PlayAnimMontage(AnimMontage);
	Actor->TakeDamage(10.0f, FDamageEvent(), Controller, GetParentActor());
	

}