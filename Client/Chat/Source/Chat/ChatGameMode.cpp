// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChatGameMode.h"
#include "ChatPlayerController.h"
#include "ChatPawn.h"

AChatGameMode::AChatGameMode()
{
	// no pawn by default
	DefaultPawnClass = AChatPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AChatPlayerController::StaticClass();
}
