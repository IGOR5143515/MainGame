// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class UBoxComponent;

UCLASS()
class MAINGAME_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool PushButton=false;
	

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value Button")
	int32 Index;

	void SetIndex(int32 NewIndex) { Index = NewIndex; }

	int32 GetIndex(){ return Index; }


	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent*  BasePlate;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Button;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent;

	UFUNCTION(BlueprintCallable)
	bool IsPushed();
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep, 
		const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
	
};
