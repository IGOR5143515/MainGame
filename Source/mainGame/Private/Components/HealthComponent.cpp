#include "Components/HealthComponent.h"
#

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Health = 100.0f;
	
}



void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}



