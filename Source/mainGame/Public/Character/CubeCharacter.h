

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CubeCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class ATowerCharacter;
class ATowerAIController;
class UMaterial;


UCLASS()
class MAINGAME_API ACubeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ACubeCharacter();

	int TraceDistance = 2000;

	FName SocketName = TEXT("GunSocket");

	FTimerHandle TimerHandle;

	bool Build = false;
	bool CanBuild = true;
	void IsBuildingMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsOverlapCube = false;

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UCameraComponent* CameraComponent;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageToCube;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Building")
	TSubclassOf<ATowerCharacter> TowerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Building")
	TSubclassOf<ATowerAIController> TowerControllerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Building")
	UMaterial* AllowedMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Building")
	UMaterial* ForbiddenMaterial;

	ATowerCharacter* GhostTower=nullptr;




public:	
	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);

	void MoveRight(float Value);
	
	void JumpCharacter();

	void StartFire();

	void StopFire();

	void MakeHit();

	void BuildingMode();

	void UpdateBuildLocation(FVector NewLocation);

	void PlaceTower();

	void CheckBuildCondition(FHitResult HitResult);


	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult);  

	UFUNCTION()
	virtual void OnDeath();

	UFUNCTION()
	virtual void OnTakeAnyDamageHandle(AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent*
		OverlappedComponent,
		AActor* OtherActor, 
		UPrimitiveComponent*
		OtherComp, int32
		OtherBodyIndex);

	
};

