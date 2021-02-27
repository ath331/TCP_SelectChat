// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChatPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class AChatPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AChatPlayerController();
};


