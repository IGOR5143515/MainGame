// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzles/Plate.h"
#include "RotatePlate.generated.h"

/**
 * 
 */
UCLASS()
class MAINGAME_API ARotatePlate : public APlate
{
	GENERATED_BODY()
public:
	virtual bool ReadyToMove()override;
};
