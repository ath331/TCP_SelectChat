// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientSocket.h"
#include "Containers/UnrealString.h"

// Sets default values
AClientSocket::AClientSocket()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AClientSocket::ConnecteToServer(FString ipStr)
{
	if (isConnected == true)
		return false;

	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	FIPv4Address ip;
	FString address = ipStr;
	int32 port = 9999;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trying to connect.")));

	bool connected = Socket->Connect(*addr);
	isConnected = true;
	if (connected)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("connected")));

		Recv();

		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("connect fail")));
		return false;
	}
}

bool AClientSocket::EnterToLobby(FString id)
{
	Recv();

	return true;
}

void AClientSocket::Send(FString str)
{
	FString loginSend = "/login aa";

	uint8 temp[BUFSIZ] = { NULL, };
	for (int i = 0; i < loginSend.Len(); i++)
	{
		temp[i] = loginSend[i];
	}
	loginSend[loginSend.Len()] = '\n';

	Socket->Send(temp, 10, bytesSend);
}


void AClientSocket::Recv()
{
	bool recv = Socket->Recv(buf, bufSize, bytesRead);

	if (recv == true && bytesRead != 0)
	{
		char ansiiData[bufSize];
		memcpy(ansiiData, buf, bytesRead);
		ansiiData[bytesRead] = 0;

		FString Fixed = TCHAR_TO_UTF8(ansiiData);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Fixed);
	}
}


// Called when the game starts or when spawned
void AClientSocket::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AClientSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

