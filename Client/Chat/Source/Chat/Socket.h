// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "CoreMinimal.h"

UFUNCTION(BlueprintCallable, Category = Socket)

/**
 *
 */
	class CHAT_API Socket
{
public:
	Socket();
	~Socket();

	FSocket* socket;
	FString address = TEXT("127.0.0.1");
	int32 port = 9999;

	FIPv4Address ip;


	bool connected;
};
