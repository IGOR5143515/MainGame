#include "Character/TowerCharacter/TowerAIController.h"
#include "AI/MyAIPerceptionComponent.h"
#include "Character/TowerCharacter/Projectile.h"
#include "Character/TowerCharacter/TowerCharacter.h"
#include "AI/AICharacter.h"
#include "Components/HealthComponent.h"


ATowerAIController::ATowerAIController()
{
	Perception->OnTargetPerceptionUpdated.AddDynamic(this,&ATowerAIController::OnTargetPerceived);
}

void ATowerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void ATowerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		Fire();
	
	

}

void ATowerAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
{
	
	if (Stimulus.WasSuccessfullySensed()&&Actor->IsA<AAICharacter>()) {
		CurrentTurget = Actor;
	}
	else
		CurrentTurget = nullptr;
	
}

void ATowerAIController::Fire()
{
	if (!CanFire)return;
	
	ATowerCharacter* TowerCharacter = Cast<ATowerCharacter>(GetPawn());
	if (!TowerCharacter)return;
	

	if (CurrentTurget && ProjectileClass) {

		if (Cast<AAICharacter>(CurrentTurget)->HealthComponent->IsDead()) {
			CurrentTurget = nullptr;
			return;
		}
		FVector Location = TowerCharacter->GetMesh()->GetSocketLocation(MuzzleName);
		FVector Direction = (CurrentTurget->GetActorLocation() - Location).GetSafeNormal(); 
		FRotator Rotation = Direction.Rotation(); 

		
	UE_LOG(LogTemp, Error, TEXT("Fire"));

		if (GetWorld()) {
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);

			if (Projectile) {
				FVector LaunchDirection = Rotation.Vector(); 
				Projectile->SetInitialVelocity(LaunchDirection);
				CanFire = false;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATowerAIController::ResetFire, 1.5f, false);
			}
		}

	}

}

