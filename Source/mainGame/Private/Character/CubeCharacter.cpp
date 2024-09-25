#include "Character/CubeCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/HealthComponent.h"
#include "AI/AICharacter.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

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
	HealthComponent->OnDeathDelegate.AddUObject(this, &ACubeCharacter::OnDeath);
	OnTakeAnyDamage.AddDynamic(this, &ACubeCharacter::OnTakeAnyDamageHandle);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACubeCharacter::OnOverlap);
}


void ACubeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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


void ACubeCharacter::StartFire()
{
	
	if(GetWorld())
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACubeCharacter::MakeHit, 0.2f, true);

	MakeHit();
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
	UE_LOG(LogTemp, Error, TEXT("OnTakeAnyDamageHandle"));
	
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
		
		
		TakeDamage(DamageToCube, FDamageEvent(), GetController(), OtherActor);
		auto AIChar = Cast<AAICharacter>(OtherActor);
		if (AIChar) {

			FVector  LaunchDirection = AIChar->GetActorLocation() - GetActorLocation();
			LaunchDirection.Z = 0;
			LaunchDirection.Normalize();

			float LaunchStrength = 2000;
			AIChar->LaunchCharacter(LaunchDirection*LaunchStrength, false, false);
		
		}
	}
}