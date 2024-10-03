#include "Character/TowerCharacter/TowerAIController.h"
#include "AI/MyAIPerceptionComponent.h"
#include "Character/TowerCharacter/Projectile.h"
#include "Character/TowerCharacter/TowerCharacter.h"
#include "AI/AICharacter.h"
#include "Components/HealthComponent.h"
#include "Perception/AISense_Sight.h"


ATowerAIController::ATowerAIController()
{
	/*Perception->OnTargetPerceptionUpdated.AddDynamic(this,&ATowerAIController::OnTargetPerceived);*/
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
//void ATowerAIController::OnTargetPerceived(AActor* Actor, FAIStimulus Stimulus)
//{
//	
//	if (Stimulus.WasSuccessfullySensed()&&Actor->IsA<AAICharacter>()) {
//		CurrentTurget = Actor;
//	}
//	else
//		CurrentTurget = nullptr;
//	
//}

void ATowerAIController::Fire()
{
	if (!CanFire)return;
	
	ATowerCharacter* TowerCharacter = Cast<ATowerCharacter>(GetPawn());
	if (!TowerCharacter)return;
	

	if (ProjectileClass) {

		/*if (Cast<AAICharacter>(CurrentTurget)->HealthComponent->IsDead()) {
			
			return;
		}*/

		AActor* FindingActor = FindCurrnetTarget();
		if (!FindingActor)return;

		FVector Location = TowerCharacter->GetMesh()->GetSocketLocation(MuzzleName);
		FVector Direction = (FindingActor->GetActorLocation() - Location).GetSafeNormal();
		FRotator Rotation = Direction.Rotation(); 


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

AActor* ATowerAIController::FindCurrnetTarget()
{
	AActor* Obj = nullptr;
	TArray<AActor*>FindingActors;

	Perception->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), FindingActors);

	float BestDistance = MAX_FLT;

	for (auto x : FindingActors) {
		if (x->IsA<AAICharacter>()) {

			float CurrnetDistance = (x->GetActorLocation() - GetPawn()->GetActorLocation()).Size();
			if (CurrnetDistance < BestDistance) {
				BestDistance = CurrnetDistance;
				Obj = x;
			}

		}
	}
	return Obj;

}

