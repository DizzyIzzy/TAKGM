#pragma once

//Networking
#include "Networking.h"

//Base
#include "CoreMinimal.h"
#include "Cot/CotSharable.h"
#include "GameFramework/Actor.h"
#include "UDPSender.generated.h"

class ACotActor;
class ACotPawn;
class ACotCharacter;

UCLASS()
class AUDPSender : public AActor
{
	GENERATED_UCLASS_BODY()

		bool IsUDP;

public:
	TSharedPtr<FInternetAddr>	RemoteAddr;
	FSocket* SenderSocket;
	double MinutesValid;

	UFUNCTION(BlueprintCallable, Category = "UDP")
		bool UDPSender_SendString(FString ToSend);

	UFUNCTION(BlueprintCallable, Category = "UDP")
		bool StartUDPSender(
			const FString& YourChosenSocketName,
			const FString& TheIP,
			const int32 ThePort
		);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UDP Sender")
		bool ShowOnScreenDebugMessages;


	//ScreenMsg
	FORCEINLINE void ScreenMsg(const FString& Msg)
	{
		if (!ShowOnScreenDebugMessages) return;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *Msg);
	}
	FORCEINLINE void ScreenMsg(const FString& Msg, const float Value)
	{
		if (!ShowOnScreenDebugMessages) return;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %f"), *Msg, Value));
	}
	FORCEINLINE void ScreenMsg(const FString& Msg, const FString& Msg2)
	{
		if (!ShowOnScreenDebugMessages) return;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %s"), *Msg, *Msg2));
	}


public:

	/** Called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	bool RelayIncomingMessage(const FArrayReaderPtr& ToSend);

	UFUNCTION(BlueprintCallable, Category = "Time")
		FString GetTime();

	UFUNCTION(BlueprintCallable, Category = "Cot")
		void BroadcastCot(bool PrintToScreen, bool PrintToLog);

	UFUNCTION(BlueprintImplementableEvent, Category = "Cot")
		FVector transformActorLocationToRealCoord(AActor* actor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Cot")
		FVector transformUECoordToRealCoord(FVector unrealCoord);

	UFUNCTION(Category = "Cot")
		FString FormCot(AActor* CotEntity);

	UFUNCTION(BlueprintCallable, Category = "Time")
		FString GetStaleTime();

	UFUNCTION(BlueprintCallable, Category = "Cot")
		FString FormXML(FString Type, FString Uid, FString Callsign, FString Stale, float Lat, float Lon, float Hae, float Ce, float Le);

	UFUNCTION(BlueprintCallable, Category = "Cot")
		void SetStaleToNow(FString Type, FString Uid, FString Callsign, FVector UnrealCoordinates);

	UFUNCTION(Category = "Cot")
		static FString FormTypeString(AActor* CotEntity);
};