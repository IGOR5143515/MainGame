// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyActor::AMyActor()
{

	PrimaryActorTick.bCanEverTick = true;

	Index = 1;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	BasePlate = CreateDefaultSubobject<UStaticMeshComponent>("BasePlate");
	Button = CreateDefaultSubobject<UStaticMeshComponent>("Button");

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AMyActor::EndOverlap);


	BasePlate->SetupAttachment(GetRootComponent());
	Button->SetupAttachment(BasePlate);
	BoxComponent->SetupAttachment(Button);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}


void AMyActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Error, TEXT("Overlapped"));
	PushButton = true;
}

void AMyActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Error, TEXT("EndOverlapped"));
	PushButton = false;
}


bool AMyActor::IsPushed()
{
	return PushButton;
}
