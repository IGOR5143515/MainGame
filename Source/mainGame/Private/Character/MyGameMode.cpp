// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyGameMode.h"
#include "Character/CubeCharacter.h"
#include "Character/MyPlayerController.h"

AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = ACubeCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();

}
