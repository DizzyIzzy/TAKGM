// Fill out your copyright notice in the Description page of Project Settings.


#include "UDP/UDPReceiver.h"

AUDPReceiver::AUDPReceiver(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ListenSocket = NULL;
}

void AUDPReceiver::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//~~~~~~~~~~~~~~~~

	delete UDPReceiver;
	UDPReceiver = nullptr;

	//Clear all sockets!
	//		makes sure repeat plays in Editor dont hold on to old sockets!
	if (ListenSocket)
	{
		ListenSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
	}
}

// Start UDP Receiver
bool AUDPReceiver::StartUDPReceiver(
	const FString& YourChosenSocketName,
	const FString& TheIP,
	const int32 ThePort
) {

	//ScreenMsg("RECEIVER INIT");
	singletonUdpSender = (AUDPSender*)UGameplayStatics::GetActorOfClass(GetWorld(), AUDPSender::StaticClass());

	FIPv4Address Addr;
	FIPv4Address::Parse(TheIP, Addr);

	//Create Socket
	FIPv4Endpoint Endpoint(Addr, ThePort);

	//BUFFER SIZE - 2 MB
	int32 BufferSize = 2 * 1024 * 1024;

	ListenSocket = FUdpSocketBuilder(*YourChosenSocketName)
		.AsNonBlocking()
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.WithReceiveBufferSize(BufferSize);
	;

	FTimespan ThreadWaitTime = FTimespan::FromMilliseconds(100);
	UDPReceiver = new FUdpSocketReceiver(ListenSocket, ThreadWaitTime, TEXT("UDP RECEIVER"));
	UDPReceiver->OnDataReceived().BindUObject(this, &AUDPReceiver::Recv);
	UDPReceiver->Start();
	return true;
}

void AUDPReceiver::Recv(const FArrayReaderPtr& ArrayReaderPtr, const FIPv4Endpoint& EndPt)
{
	// Relay the CoT Message
	if (!singletonUdpSender) {
		UE_LOG(LogTemp, Log, TEXT("DID NOT RELAY COT: singletonUdpSender in BP_UDPReceiver is null!"));
	}
	else {
		singletonUdpSender->RelayIncomingMessage(ArrayReaderPtr);
	}


	FString Data = FString(UTF8_TO_TCHAR(ArrayReaderPtr->GetData()));

	FGraphEventRef Task = FFunctionGraphTask::CreateAndDispatchWhenReady([this, Data]()
	{

		parseIncomingCot(Data);
	}, TStatId(), NULL, ENamedThreads::GameThread);
	UE_LOG(LogTemp, Log, TEXT("****UDP**** Data received: %s"), *Data);
}

