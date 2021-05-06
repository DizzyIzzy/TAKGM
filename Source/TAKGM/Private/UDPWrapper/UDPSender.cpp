/*

	UDPSender

*/
//#include "UDPSendReceive.h"
#include "UDPWrapper/UDPSender.h"
#include "UDPWrapper/UDPData.h"

AUDPSender::AUDPSender(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SenderSocket = NULL;

	ShowOnScreenDebugMessages = true;
}

void AUDPSender::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//~~~~~~~~~~~~~~~~

	if (SenderSocket)
	{
		SenderSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(SenderSocket);
	}
}

bool AUDPSender::StartUDPSender(
	const FString& YourChosenSocketName,
	const FString& TheIP,
	const int32 ThePort
) {
	//Create Remote Address.
	RemoteAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	bool bIsValid;
	RemoteAddr->SetIp(*TheIP, bIsValid);
	RemoteAddr->SetPort(ThePort);

	if (!bIsValid)
	{
		ScreenMsg("UDP Sender>> IP address was not valid!", TheIP);
		return false;
	}

	SenderSocket = FUdpSocketBuilder(*YourChosenSocketName)
		.AsReusable()
		.WithBroadcast()
		;


	//check(SenderSocket->GetSocketType() == SOCKTYPE_Datagram);

	//Set Send Buffer Size
	int32 SendSize = 2 * 1024 * 1024;
	SenderSocket->SetSendBufferSize(SendSize, SendSize);
	SenderSocket->SetReceiveBufferSize(SendSize, SendSize);

	UE_LOG(LogTemp, Log, TEXT("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
	UE_LOG(LogTemp, Log, TEXT("****UDP**** Sender Initialized Successfully!!!"));
	UE_LOG(LogTemp, Log, TEXT("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n"));

	return true;
}

bool AUDPSender::UDPSender_SendString(FString ToSend)
{
	if (!SenderSocket)
	{
		ScreenMsg("No sender socket");
		return false;
	}
	//~~~~~~~~~~~~~~~~

	int32 BytesSent = 0;

	FUDPData NewData;
	NewData.CoTMessage = ToSend;

	FArrayWriter Writer;

	Writer << NewData; //Serializing our custom data, thank you UE4!

	SenderSocket->SendTo(Writer.GetData(), Writer.Num(), BytesSent, *RemoteAddr);

	if (BytesSent <= 0)
	{
		const FString Str = "Socket is valid but the receiver received 0 bytes, make sure it is listening properly!";
		UE_LOG(LogTemp, Error, TEXT("%s"), *Str);
		ScreenMsg(Str);
		return false;
	}

	ScreenMsg("UDP~ Send Succcess! Bytes Sent = ", BytesSent);

	return true;
}