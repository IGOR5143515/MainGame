#include "Character/CubeCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/HealthComponent.h"
#include "AI/AICharacter.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Character/TowerCharacter/TowerCharacter.h"
#include "Character/TowerCharacter/TowerAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ACubeCharacter::ACubeCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	
	SpringArm->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealtComponent");

}



void ACubeCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(CameraComponent);
	check(SpringArm);
	check(HealthComponent);

	HealthComponent->OnDeathDelegate.AddUObject(this, &ACubeCharacter::OnDeath);
	OnTakeAnyDamage.AddDynamic(this, &ACubeCharacter::OnTakeAnyDamageHandle);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACubeCharacter::OnOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACubeCharacter::EndOverlap);
}



void ACubeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Build)
		BuildingMode();

}


void ACubeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACubeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACubeCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnRound", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LoockUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACubeCharacter::JumpCharacter);
	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACubeCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ACubeCharacter::StopFire);
	
	PlayerInputComponent->BindAction("BuildingMode", IE_Pressed, this, &ACubeCharacter::IsBuildingMode);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACubeCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACubeCharacter::StopRun);
}

void ACubeCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ACubeCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ACubeCharacter::JumpCharacter()
{
	LaunchCharacter(FVector(0, 0, 500), false, false);
}

void ACubeCharacter::Run()
{
	auto Movement =Cast<UCharacterMovementComponent>(GetMovementComponent());
	Movement->MaxWalkSpeed = 1000.0f;
	
}

void ACubeCharacter::StopRun()
{
	auto Movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	Movement->MaxWalkSpeed = 600.0f;
}

void ACubeCharacter::StartFire()
{
	
	if (Build) {
		PlaceTower();
		return;
	}
	//if(GetWorld())
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACubeCharacter::MakeHit, 0.2f, true);
		 
	//MakeHit();
}

void ACubeCharacter::StopFire()
{
	if (GetWorld())
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void ACubeCharacter::MakeHit()
{
	FVector SocketLocation = GetMesh()->GetSocketLocation(SocketName);

	FVector Location;
	FRotator Rotation;

	auto PlayerController = Cast<APlayerController>(Controller);
	PlayerController->GetPlayerViewPoint(Location, Rotation);

	FVector TraceStart = Location;
	FVector Dir = Rotation.Vector();
	FVector TraceEnd = Location + (Dir * TraceDistance);

	FHitResult HitResult;
	FCollisionQueryParams COQP;
	COQP.AddIgnoredActor(this);
	FCollisionResponseParams ColRes;
	GetWorld()->LineTraceSingleByChannel(HitResult,
		TraceStart,
		TraceEnd, ECollisionChannel::ECC_Visibility,
		COQP, ColRes);
	DrawDebugLine(GetWorld(), SocketLocation, TraceEnd, FColor::Green, false, 1.0f);

	if (HitResult.bBlockingHit) {
		UE_LOG(LogTemp, Error, TEXT("Cube"));
		HitResult.GetActor()->TakeDamage(10.0f, FDamageEvent(), Controller, GetParentActor());
	}
}




void ACubeCharacter::OnDeath()
{
	
	SetLifeSpan(0.1f);
}

void ACubeCharacter::OnTakeAnyDamageHandle(AActor* DamagedActor, 
	float Damage,
	const UDamageType* 
	DamageType,
	AController* InstigatedBy,
	AActor* DamageCauser)
{

	
	HealthComponent->TakeDamage(Damage);
	
	if (HealthComponent->IsDead())
		HealthComponent->OnDeathDelegate.Broadcast();
}


void ACubeCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AAICharacter>()) {

	IsOverlapCube = true;
	}

	/*if (OtherActor->IsA<AAICharacter>()) {
		
		
		TakeDamage(DamageToCube, FDamageEvent(), GetController(), OtherActor);
		auto AIChar = Cast<AAICharacter>(OtherActor);
		if (AIChar) {

			FVector  LaunchDirection = AIChar->GetActorLocation() - GetActorLocation();
			LaunchDirection.Z = 0;
			LaunchDirection.Normalize();

			float LaunchStrength = 2000;
			AIChar->LaunchCharacter(LaunchDirection*LaunchStrength, false, false);
		
		}
	}*/

}

void ACubeCharacter::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA<AAICharacter>()) {

		IsOverlapCube = false;
	}
	
}

void ACubeCharacter::IsBuildingMode()
{
	if (!Build) {
		Build = true;
		FActorSpawnParameters SpawnParametrs;
		SpawnParametrs.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GhostTower = GetWorld()->SpawnActor<ATowerCharacter>(TowerClass, SpawnParametrs);				//Spawning GhostTower 
		GhostTower->SetActorEnableCollision(false);
		GhostTower->GetMesh()->SetMaterial(0,AllowedMaterial);
		if (!GhostTower)return;

		return;
	}

	if (Build) {
		Build = false;
		
		GhostTower->Destroy();		//Destroy GhostTower
		GhostTower = nullptr;
		return;
	}

	
}
void ACubeCharacter::BuildingMode()
{

	if (!GetWorld()||!TowerClass)return;

	
	FVector Location;
	FRotator Rotation;

	auto PlayerController = Cast<APlayerController>(Controller);
	PlayerController->GetPlayerViewPoint(Location, Rotation);

	FVector TraceStart = Location;
	FVector Dir = Rotation.Vector();
	FVector TraceEnd = Location + (Dir * TraceDistance);

	FHitResult HitResult;
	FCollisionQueryParams COQP;
	COQP.AddIgnoredActor(this);
	FCollisionResponseParams ColRes;
	GetWorld()->LineTraceSingleByChannel(HitResult,
	TraceStart,
	TraceEnd, ECollisionChannel::ECC_Visibility,
	COQP, ColRes);

	if (HitResult.bBlockingHit) {
		CheckBuildCondition(HitResult);
		UpdateBuildLocation(HitResult.Location);
	}

}

void ACubeCharacter::UpdateBuildLocation(FVector NewLocation)
{
	int AdjustedLocation = 75;
	NewLocation.Z += AdjustedLocation;
	if(GhostTower)
	GhostTower->SetActorLocation(NewLocation);


}

void ACubeCharacter::PlaceTower()
{
	if (!GetWorld())return;
	if (!CanBuild)return;   

	FActorSpawnParameters SpawnParametrs;
	SpawnParametrs.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ATowerCharacter *Tower = GetWorld()->SpawnActor<ATowerCharacter>(TowerClass,GhostTower->GetActorLocation(),GhostTower->GetActorRotation(), SpawnParametrs);
	if (!Tower)return;

	Coins = FMath::Clamp(Coins - 25, 0, 100);
	
}

void ACubeCharacter::CheckBuildCondition(FHitResult HitResult)
{
	if (!GetWorld())return;
	float MaxAllowedSlope = 45.0f;
	FVector Normal = HitResult.Normal;
	FVector BuildLocation = HitResult.Location;

	float SlopeAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(Normal, FVector::UpVector)));
	if (SlopeAngle > MaxAllowedSlope) 
	{
		CanBuild = false;  
		GhostTower->GetMesh()->SetMaterial(0, ForbiddenMaterial); 
		return;
		
	}
	else
		CanBuild = true;
		GhostTower->GetMesh()->SetMaterial(0, AllowedMaterial);

		if (Coins <25) {
			CanBuild = false;
			GhostTower->GetMesh()->SetMaterial(0, ForbiddenMaterial);
		}
		else {
			CanBuild = true;
			GhostTower->GetMesh()->SetMaterial(0, AllowedMaterial);
		}
}
