// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChatPlayerController.h"

AChatPlayerController::AChatPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
