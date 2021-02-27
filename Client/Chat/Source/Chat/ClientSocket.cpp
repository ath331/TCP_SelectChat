// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientSocket.h"

// Sets default values
AClientSocket::AClientSocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AClientSocket::ConnectServer(std::string ipStr)
{
	FString fStr(ipStr.c_str());
	FIPv4Address ip;
	FIPv4Address::Parse(fStr, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trying to connect.")));

	connected = socket->Connect(*addr);
	if (connected)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connected.")));

	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connected Fail.")));
}


// Called when the game starts or when spawned
void AClientSocket::BeginPlay()
{
	//UE_LOG(LogTemp, Log, TEXT("ClientSocketBeginPlay()"));

	Super::BeginPlay();

	socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
}

// Called every frame
void AClientSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Log, TEXT("ClientSocketTick()"));

}

