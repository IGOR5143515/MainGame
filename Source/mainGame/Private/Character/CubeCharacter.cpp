// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CubeCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
// Sets default values
ACubeCharacter::ACubeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	
	SpringArm->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArm);



}

// Called when the game starts or when spawned
void ACubeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACubeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACubeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACubeCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnRound", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LoockUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACubeCharacter::JumpCharacter);
	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACubeCharacter::StartFire);

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

	

	FVector SocketLocation = GetMesh()->GetSocketLocation(SocketName);

	FVector Location;
	FRotator Rotation;

	auto PlayerController = Cast<APlayerController>(Controller);
	PlayerController->GetPlayerViewPoint(Location, Rotation);

	FVector TraceStart = Location;
	FVector Dir = Rotation.Vector();
	FVector TraceEnd = Location + (Dir* TraceDistance);

	FHitResult HitResult;
	FCollisionQueryParams COQP; 
	COQP.AddIgnoredActor(this);
	FCollisionResponseParams ColRes;
	GetWorld()->LineTraceSingleByChannel(HitResult,
		TraceStart,
		TraceEnd, ECollisionChannel::ECC_Visibility,
		COQP, ColRes);

	DrawDebugLine(GetWorld(), SocketLocation, TraceEnd, FColor::Green,false,1.0f);





}

