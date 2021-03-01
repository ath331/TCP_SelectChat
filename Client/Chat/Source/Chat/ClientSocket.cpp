// Fill out your copyright notice in the Description page of Project Settings.

#include <stdlib.h>
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
	Socket->SetNonBlocking(true);

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
		Recv();
		isConnected = true;

		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("connect fail")));
		return false;
	}
}

void AClientSocket::SendMessage(UPARAM(ref) const FString& chat)
{
	FString loginSend;
	loginSend += *chat;
	loginSend += "\n";
	const TCHAR* b = *loginSend;

	char sendBuf[1024]{};
	size_t size = wcstombs(sendBuf, b, sizeof(b) * 2);

	for (int i = 0; i < sizeof(sendBuf); i++)
	{
		Socket->Send((const uint8*)& sendBuf[i], 1, bytesSend);
	}
}

void AClientSocket::ShowUserList()
{
	Send("/ul", " ");
}

void AClientSocket::ShowRoomList()
{
	Send("/rl", " ");
}

void AClientSocket::SendMakeRoom(UPARAM(ref) const FString& name, UPARAM(ref) const FString& maxPersocCount, UPARAM(ref) const FString& password)
{
	FString str = name + " " + maxPersocCount + " " + password;
	Send("/mr", str);
}

void AClientSocket::SendEnterRoom(UPARAM(ref) const FString& num, UPARAM(ref) const FString& password)
{
	FString str = num + " " + password;
	Send("/re", str);
}

void AClientSocket::SendOutRoom()
{
	Send("/q", " ");
}

bool AClientSocket::EnterToLobby(FString id)
{
	if (isConnected == false)
		return false;

	Send("/login ", id);
	//Recv();

	return true;
}

void AClientSocket::Send(FString commands, FString str)
{
	FString loginSend = commands;
	loginSend += *str;
	loginSend += "\n";
	const TCHAR* b = *loginSend;

	char sendBuf[1024]{};
	size_t size = wcstombs(sendBuf, b, sizeof(b) * 2);

	for (int i = 0; i < sizeof(sendBuf); i++)
	{
		Socket->Send((const uint8*)& sendBuf[i], 1, bytesSend);
	}
}


void AClientSocket::PashingStr()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, bufStr);

	if (bufStr == "IsLoginedTrue")
	{
		OffLoginUI();
	}
	else
	{
		if (bufStr[0] == '(' && bufStr[1] == '#')
		{
			listCount = (int32)bufStr[2] - 48;
			isUserList = true;
			bufStr.Empty();
			return;
		}

		else if (bufStr[0] == '(' && bufStr[1] == '$')
		{
			listCount = (int32)bufStr[2] - 48;
			isRoomList = true;
			bufStr.Empty();
			return;
		}

		if (isUserList == true && listCount > 0)
		{
			UploadUserList(bufStr);
			--listCount;
			if (listCount == 0)
				isUserList = false;
			bufStr.Empty();
		}

		else if (isRoomList == true && listCount > 0)
		{
			UploadRoomList(bufStr);
			--listCount;
			if (listCount == 0)
				isRoomList = false;
			bufStr.Empty();
		}

		else
			UploadChat(bufStr);
	}

	bufStr.Empty();
}


void AClientSocket::Recv()
{
	if (Socket == nullptr)
		return;

	bool recv = Socket->Recv(buf, 1, bytesRead);

	if (recv == true && bytesRead != 0)
	{
		char ansiiData[bufSize];
		memcpy(ansiiData, buf, bytesRead);
		ansiiData[bytesRead] = 0;

		FString Fixed = ANSI_TO_TCHAR(ansiiData);

		if (Fixed != "\n")
			bufStr.Append(Fixed);
		else
			PashingStr();
	}
}


// Called when the game starts or when spawned
void AClientSocket::BeginPlay()
{
	Super::BeginPlay();
	//OffLoginUI();
}

// Called every frame
void AClientSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Recv();
}

