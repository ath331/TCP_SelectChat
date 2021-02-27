// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>

#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClientSocket.generated.h"

const int32 defaultPort = 9999;

UCLASS()
class CHAT_API AClientSocket : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AClientSocket();

	FSocket* socket;
	int32 port = defaultPort;

	bool connected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float test;

	UFUNCTION(BlueprintCallable)
		void ConnectServer(std::string ip);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
