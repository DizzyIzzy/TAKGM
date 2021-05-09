/*

	UDPSender

*/
//#include "UDPSendReceive.h"
#include "UDPWrapper/UDPSender.h"
#include "UDPWrapper/UDPData.h"
#include "Misc/DateTime.h"

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

	SenderSocket->SendTo(Writer.GetData() + 4, Writer.Num() - 5, BytesSent, *RemoteAddr);

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

FString AUDPSender::GetTime()
{
	FDateTime now = FDateTime().UtcNow();

	int32 day = now.GetDay();
	int32 month = now.GetMonth();
	int32 hour = now.GetHour();
	int32 minute = now.GetMinute();
	int32 second = now.GetSecond();

	FString nowFormatted = FString::FromInt(now.GetYear());
	nowFormatted += FString(TEXT("-"));
	if (month < 10)
		nowFormatted += FString(TEXT("0"));
	nowFormatted += FString::FromInt(month);
	nowFormatted += FString(TEXT("-"));
	if (day < 10)
		nowFormatted += FString(TEXT("0"));
	nowFormatted += FString::FromInt(day);
	nowFormatted += FString(TEXT("T"));
	if (hour < 10)
		nowFormatted += FString(TEXT("0"));
	nowFormatted += FString::FromInt(hour);
	nowFormatted += FString(TEXT(":"));
	if (minute < 10)
		nowFormatted += FString(TEXT("0"));
	nowFormatted += FString::FromInt(minute);
	nowFormatted += FString(TEXT(":"));
	if (second < 10)
		nowFormatted += FString(TEXT("0"));
	nowFormatted += FString::FromInt(second);
	nowFormatted += FString(TEXT("Z"));
	return nowFormatted;
}

FString AUDPSender::GetStaleTime(float MinutesValid)
{
	FTimespan addedMinutes;
	addedMinutes.FromMinutes(MinutesValid);
	FDateTime stale = FDateTime().UtcNow() + addedMinutes;

	int32 day = stale.GetDay();
	int32 month = stale.GetMonth();
	int32 hour = stale.GetHour();
	int32 minute = stale.GetMinute();
	int32 second = stale.GetSecond();

	FString staleFormatted = FString::FromInt(stale.GetYear());
	staleFormatted += FString(TEXT("-"));
	if (month < 10)
		staleFormatted += FString(TEXT("0"));
	staleFormatted += FString::FromInt(month);
	staleFormatted += FString(TEXT("-"));
	if (day < 10)
		staleFormatted += FString(TEXT("0"));
	staleFormatted += FString::FromInt(day);
	staleFormatted += FString(TEXT("T"));
	if (hour < 10)
		staleFormatted += FString(TEXT("0"));
	staleFormatted += FString::FromInt(hour);
	staleFormatted += FString(TEXT(":"));
	if (minute < 10)
		staleFormatted += FString(TEXT("0"));
	staleFormatted += FString::FromInt(minute);
	staleFormatted += FString(TEXT(":"));
	if (second < 10)
		staleFormatted += FString(TEXT("0"));
	staleFormatted += FString::FromInt(second);
	staleFormatted += FString(TEXT("Z"));
	return staleFormatted;
}

FString AUDPSender::FormXML(FString Type, FString Uid, float MinutesValid, float Lat, float Lon, float Hae, FString Ce, FString Le) 
{
	FString Time = GetTime();
	FString Stale = GetStaleTime(MinutesValid);

	//FString xml = FString(TEXT("<?xml version=\"1.0\"?>");
	FString xml = FString(TEXT("<event version=\"2.0\" uid=\""));
	xml += Uid;
	xml += FString(TEXT("\" type=\""));
	xml += Type;
	xml += FString(TEXT("\" how=\"m-g\" time=\""));
	xml += Time;
	xml += FString(TEXT("\" start=\""));
	xml += Time;
	xml += FString(TEXT("\" stale=\""));
	xml += Stale;
	xml += FString(TEXT("\" > <detail><contact callsign=\"Survivor2\" /><remarks /></detail><point lat=\""));
	xml += FString::SanitizeFloat(Lat);
	xml += FString(TEXT("\" lon=\""));
	xml += FString::SanitizeFloat(Lon);
	xml += FString(TEXT("\" ce=\""));
	xml += Ce;
	xml += FString(TEXT("\" hae=\""));
	xml += FString::SanitizeFloat(Hae);
	xml += FString(TEXT("\" le=\""));
	xml += Le;
	xml += FString(TEXT("\" /></event>"));
	return xml;
}