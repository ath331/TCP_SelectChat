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
	if (connected)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("connected")));

		FString loginSend = "/login aa\n";

		StringToBytes(loginSend,bufSend,10);
		Socket->Send(bufSend,10,bytesSend);

		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("connect fail")));
		return false;
	}
}

bool AClientSocket::EnterToLobby(FString ip, FString id)
{
	if (ConnecteToServer(ip) == false)
		return false;

	bool recv = Socket->Recv(buf, bufSize, bytesRead);
	if (recv == true && bytesRead != 0)
	{
		char ansiiData[bufSize];
		memcpy(ansiiData, buf, bytesRead);
		ansiiData[bytesRead] = 0;

		FString Fixed = ANSI_TO_TCHAR(ansiiData);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Fixed);
	}
	return true;
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

