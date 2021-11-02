/*

	UDPSender

*/

#include "UDP/UDPSender.h"
#include "UDP/UDPData.h"
#include "Cot/CotSharable.h"
#include "Misc/DateTime.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

AUDPSender::AUDPSender(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SenderSocket = NULL;

	ShowOnScreenDebugMessages = true;

	MinutesValid = 10.0;
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

	//Set Send Buffer Size
	int32 SendSize = 2 * 1024 * 1024;
	SenderSocket->SetSendBufferSize(SendSize, SendSize);
	SenderSocket->SetReceiveBufferSize(SendSize, SendSize);

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

	Writer << NewData;

	if (SenderSocket->GetConnectionState() != ESocketConnectionState::SCS_Connected) {
		return false;
	}

	SenderSocket->SendTo(Writer.GetData() + 4, Writer.Num() - 5, BytesSent, *RemoteAddr);

	if (BytesSent <= 0)
	{
		const FString Str = "Socket is valid but the receiver received 0 bytes, make sure it is listening properly!";
		UE_LOG(LogTemp, Error, TEXT("%s"), *Str);
		ScreenMsg(Str);
		return false;
	}

	return true;
}

bool AUDPSender::RelayIncomingMessage(const FArrayReaderPtr &ToSend)
{
	if (!SenderSocket)
	{
		ScreenMsg("No sender socket");
		return false;
	}
	//~~~~~~~~~~~~~~~~

	int32 BytesSent = 0;

	if (SenderSocket->GetConnectionState() != ESocketConnectionState::SCS_Connected) {
		return false;
	}
	UE_LOG(LogTemp, Log, TEXT("RELAYING COT!"));
	SenderSocket->SendTo(ToSend->GetData(), ToSend->Num(), BytesSent, *RemoteAddr);

	if (BytesSent <= 0)
	{
		const FString Str = "FAILED TO RELAY COT: Socket is valid but the receiver received 0 bytes!";
		UE_LOG(LogTemp, Error, TEXT("%s"), *Str);
		ScreenMsg(Str);
		return false;
	}

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

void AUDPSender::BroadcastCot(bool PrintToScreen, bool PrintToLog)
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(GWorld, UCotSharable::StaticClass(), Actors);
	for (AActor* Actor : Actors) {
		if (!IsValid(Actor)) {
			continue;
		}

		ICotSharable* CotSharableActor = Cast<ICotSharable>(Actor);
		
		if (CotSharableActor == nullptr) {
			continue;
		}

		if (ICotSharable::Execute_GetIsStale(Actor) || !ICotSharable::Execute_GetShouldSendCoT(Actor)) {
			continue;
		}

		FString CotXML = AUDPSender::FormCot(Actor);

		if (AUDPSender::UDPSender_SendString(CotXML))
		{
			if (GEngine && PrintToScreen)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, (TEXT("Sent Cot: %s"), *CotXML));

			if (PrintToLog)
				UE_LOG(LogTemp, Warning, TEXT("Sent Cot: %s"), *CotXML);
		}
		else
		{
			if (GEngine && PrintToScreen)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, (TEXT("Failed to send Cot: %s"), *CotXML));

			if (PrintToLog)
				UE_LOG(LogTemp, Warning, TEXT("Failed to send Cot: %s"), *CotXML);
		}
	}
}

FString AUDPSender::FormCot(AActor* CotEntity)
{
	FVector longLatHeight = AUDPSender::transformActorLocationToRealCoord(CotEntity);
	FString Stale = GetStaleTime();
	return AUDPSender::FormXML(AUDPSender::FormTypeString(CotEntity),
		ICotSharable::Execute_GetUid(CotEntity),
		ICotSharable::Execute_GetCallsign(CotEntity),
		Stale,
		longLatHeight.Y,
		longLatHeight.X,
		longLatHeight.Z,
		10.0f,
		10.0f);
}

FString AUDPSender::FormTypeString(AActor* CotEntity) {
	FString affiliation;

	switch (ICotSharable::Execute_GetAffiliation(CotEntity)) {
		case ECotAffiliation::AFFIL_Friendly:
			affiliation = FString("f-");
			break;
		case ECotAffiliation::AFFIL_Neutral:
			affiliation = FString("n-");
			break;
		case ECotAffiliation::AFFIL_Other:
			affiliation = FString("x-");
			break;
		case ECotAffiliation::AFFIL_Hostile:
		default:
			affiliation = FString("h-");
			break;
	}
	return FString("a-") + affiliation + ICotSharable::Execute_GetType(CotEntity);
}

FString AUDPSender::GetStaleTime()
{
	// FromMinutes() takes a double, unreal BP does not support doubles
	double mv = MinutesValid;
	FTimespan addedMinutes = FTimespan::FromMinutes(mv);
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

FString AUDPSender::FormXML(FString Type, FString Uid, FString Callsign, FString Stale, float Lat, float Lon, float Hae, float Ce, float Le)
{
	FString Time = GetTime();

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
	xml += FString(TEXT("\" > <detail><contact callsign=\""));
	xml += Callsign;
	xml += FString(TEXT("\" /><remarks /></detail><point lat=\""));
	xml += FString::SanitizeFloat(Lat);
	xml += FString(TEXT("\" lon=\""));
	xml += FString::SanitizeFloat(Lon);
	xml += FString(TEXT("\" ce=\""));
	xml += FString::SanitizeFloat(Ce);
	xml += FString(TEXT("\" hae=\""));
	xml += FString::SanitizeFloat(Hae);
	xml += FString(TEXT("\" le=\""));
	xml += FString::SanitizeFloat(Le);
	xml += FString(TEXT("\" /></event>"));
	return xml;
}

void AUDPSender::SetStaleToNow(FString Type, FString Uid, FString Callsign, FVector UnrealCoordinates) {
	FVector longLatHeight = AUDPSender::transformUECoordToRealCoord(UnrealCoordinates);
	FString xml = this->FormXML(Type,
		Uid,
		Callsign,
		GetTime(),
		longLatHeight.Y,
		longLatHeight.X,
		longLatHeight.Z,
		10.0f,
		10.0f
	);
	this->UDPSender_SendString(xml);
}
