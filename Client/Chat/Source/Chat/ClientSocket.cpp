// Fill out your copyright notice in the Description page of Project Settings.

#include "ClientSocket.h"
#include <stdlib.h>
#include <string>
#include "Containers/UnrealString.h"

// Sets default values
AClientSocket::AClientSocket()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	setlocale(LC_ALL, "Korean");
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

	Socket->Send((const uint8*)&sendBuf, sizeof(b) * 2, bytesSend);
}

void AClientSocket::ShowUserList()
{
	if (isConnected == false)
		return;
	Send("/ul", " ");
}

void AClientSocket::ShowRoomList()
{
	if (isConnected == false)
		return;
	Send("/rl", " ");
}

void AClientSocket::SendMakeRoom(UPARAM(ref) const FString& name, UPARAM(ref) const FString& maxPersocCount, UPARAM(ref) const FString& password)
{
	if (isConnected == false)
		return;
	FString str = name + " " + maxPersocCount + " " + password;
	Send("/mr ", str);
}

void AClientSocket::SendEnterRoom(UPARAM(ref) const FString& num, UPARAM(ref) const FString& password)
{
	if (isConnected == false)
		return;
	FString str = num + " " + password;
	Send("/re ", str);
}

void AClientSocket::SendOutRoom()
{
	if (isConnected == false)
		return;
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

void AClientSocket::SendRoomInfo()
{
	if (isConnected == false)
		return;
	Send("/ri ", "");
}


void AClientSocket::Send(FString commands, FString str)
{
	FString loginSend = commands;
	loginSend += *str;
	loginSend += "\n";
	const TCHAR* b = *loginSend;

	char sendBuf[1024]{};
	size_t size = wcstombs(sendBuf, b, sizeof(b) * 2);

	if (Socket != nullptr)
		Socket->Send((const uint8*)&sendBuf, sizeof(b) * 2, bytesSend);
}

void AClientSocket::SendQuitProgram()
{
	Send("/quit ", "");
}


void AClientSocket::PashingStr()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, bufStr);
	if (bufStr == "")
		return;

	if (bufStr == "IsLoginedTrue")
	{
		OffLoginUI();
	}

	else if (bufStr == "IsEnterRoomTrue")
	{
		EnterRoom();
	}

	else if (bufStr[0] == '(' && bufStr[1] == '#')
	{
		listCount = (int32)bufStr[2] - 48;
		isUserList = true;
	}

	else if (bufStr[0] == '(' && bufStr[1] == '$')
	{
		listCount = (int32)bufStr[2] - 48;
		isRoomList = true;
	}

	else
	{
		if (isUserList == true && listCount > 0)
		{
			UploadUserList(bufStr);
			--listCount;
			if (listCount == 0)
				isUserList = false;
		}

		else if (isRoomList == true && listCount > 0)
		{
			UploadRoomList(bufStr);
			--listCount;
			if (listCount == 0)
				isRoomList = false;
		}

		else
			UploadChat(bufStr);
	}


	totalStr = totalStr.Mid(bufStr.Len()+1, totalStr.Len());
	bufStr.Empty();
}


void AClientSocket::Recv() //TIck에서 계속 호출되고 있다
{
	if (Socket == nullptr)
		return;

	if (totalStr.Len() > 0)
	{
		for (int i = 0; i < totalStr.Len(); i++)
		{
			if (totalStr[i] == '\n')
			{
				bufStr = totalStr.Mid(0, i);
				PashingStr();
				break;
			}
		}

		if (bufStr == "")
			return;
	}

	bool recv = Socket->Recv(buf, bufSize, bytesRead);
	if (recv == true && bytesRead != 0)
	{
		char ansiiData[bufSize];
		memcpy(ansiiData, buf, sizeof(buf));
		ansiiData[bytesRead] = 0;

		TCHAR wstr[1024]{};
		size_t size = mbstowcs(wstr, ansiiData, sizeof(ansiiData) * 2);

		FString Fixed(wstr);
		totalStr += Fixed;

		for (int i = 0; i < totalStr.Len(); i++)
		{
			if (totalStr[i] == '\n')
			{
				bufStr = totalStr.Mid(0, i);
				PashingStr();
				break;
			}
		}

		if (bufStr == "")
			return;

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

