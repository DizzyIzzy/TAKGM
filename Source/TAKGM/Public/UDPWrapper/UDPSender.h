#pragma once

//Networking
#include "Networking.h"

//Base
#include "UDPSender.generated.h"

UCLASS()
class AUDPSender : public AActor
{
	GENERATED_UCLASS_BODY()

		bool IsUDP;


	UFUNCTION(BlueprintCallable, Category = "UDP")
	bool UDPSender_SendString(FString ToSend);

public:
	TSharedPtr<FInternetAddr>	RemoteAddr;
	FSocket* SenderSocket;

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
};