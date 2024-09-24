

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAINGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UHealthComponent();
	FOnDeath OnDeathDelegate; // подписатся на делегат в чарактере

protected:
	
	virtual void BeginPlay() override;

	float Health;
	float MaxHealth=100;

public:	
	void TakeDamage(float Value) {

		UE_LOG(LogTemp, Error, TEXT("%f"), Health);
		FMath::Clamp(Health = Health - Value, 0, MaxHealth);
	}

	bool IsDead() { return Health <= 0.0f; }
	float GetHealth() { return Health; }
	void SetHealth(float Value) { Health = Value; }
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	

};
