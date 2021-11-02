// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Networking.h"
#include "GameFramework/Actor.h"
#include "Containers/UnrealString.h"
#include "Async/TaskGraphInterfaces.h"
#include "UDP/UDPSender.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "UDPReceiver.generated.h"

UCLASS()
class AUDPReceiver : public AActor
{
	GENERATED_UCLASS_BODY()

		//====================================================
		//		Data Received Events!

public:
	/** Data has been received!! */
	UFUNCTION(BlueprintImplementableEvent)
		void BPEvent_DataReceived(const FString& ReceivedData);
	//====================================================

	UPROPERTY(EditDefaultsOnly, Category="Cot")
		TSubclassOf<AActor> StandInActorClass;

public:
	FSocket* ListenSocket;

	AUDPSender* singletonUdpSender;
	FUdpSocketReceiver* UDPReceiver = nullptr;
	void Recv(const FArrayReaderPtr& ArrayReaderPtr, const FIPv4Endpoint& EndPt);

	UFUNCTION(BlueprintCallable, Category = "UDP")
	bool StartUDPReceiver(
		const FString& YourChosenSocketName,
		const FString& TheIP,
		const int32 ThePort
	);

	//ScreenMsg
	FORCEINLINE void ScreenMsg(const FString& Msg)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *Msg);
	}
	FORCEINLINE void ScreenMsg(const FString& Msg, const float Value)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %f"), *Msg, Value));
	}
	FORCEINLINE void ScreenMsg(const FString& Msg, const FString& Msg2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %s"), *Msg, *Msg2));
	}


public:

	/** Called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Cot")
		void parseIncomingCot(const FString& message);
};
