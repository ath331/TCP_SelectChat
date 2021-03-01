﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
const int32 bufSize = 1024;
#include <clocale>

#include "Engine.h"
#include "Networking.h"
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
	~AClientSocket()
	{
		setlocale(LC_ALL, "Korean");
		if (Socket != nullptr)
			Socket->Close();
	}
	FSocket* Socket;

	uint8 buf[bufSize];
	uint8 bufSend[bufSize];
	int32 bytesRead;
	int32 bytesSend;

	FString bufStr;

	bool isConnected = false;

	UPROPERTY();
	bool isLogined = false;

	UFUNCTION(BlueprintCallable)
		void ShowUserList();
	UFUNCTION(BlueprintCallable)
		void ShowRoomList();
	UFUNCTION(BlueprintCallable)
		bool ConnecteToServer(FString ip = TEXT("127.0.0.1"));
	UFUNCTION(BlueprintCallable)
		bool EnterToLobby(FString id = TEXT("defaultID"));
	UFUNCTION(BlueprintCallable)
		void SendMessage(UPARAM(ref) const FString& chat);

	UFUNCTION(BlueprintImplementableEvent)
		void OffLoginUI();
	UFUNCTION(BlueprintImplementableEvent)
		void UploadChat(const FString& chat);
	UFUNCTION(BlueprintImplementableEvent)
		void MakeRoom( const FString& roomName, const FString& MaxPerson, const FString& password = TEXT("@!2209ASd"));
	UFUNCTION(BlueprintImplementableEvent)
		void EnterRoom( const FString& roomNum, const FString& password = TEXT("@!2209ASd"));


	void Recv();
	void Send(FString commands, FString str);

	void PashingStr();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
