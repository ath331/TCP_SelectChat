// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClientSocket.generated.h"

UCLASS()
class CHAT_API AClientSocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClientSocket();

	FSocket* socket;
	FString address = TEXT("127.0.0.1");
	int32 port = 9999;

	FIPv4Address ip;

	bool connected;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
