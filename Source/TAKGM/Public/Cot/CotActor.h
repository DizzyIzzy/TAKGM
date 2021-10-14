// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"
#include "CotSharable.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "CotActor.generated.h"

// Forward class declaration to avoid circular dependency -> included in .cpp file
class AUDPSender;

UCLASS()
class TAKGM_API ACotActor : public AActor, public ICotSharable
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		FString Uid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		FString Callsign;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		AUDPSender* singletonUDPSender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		bool isStale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		bool ShouldSendCoT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		ECotAffiliation Affiliation;

	// Constructor
	ACotActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// virtual void BeginDestroy();

	// Implements functions from ICotSharable
	virtual FString GetType_Implementation() override;

	virtual FString GetUid_Implementation() override;

	virtual FString GetCallsign_Implementation() override;

	virtual float GetLatitude_Implementation() override;

	virtual float GetLongitude_Implementation() override;

	virtual float GetHae_Implementation() override;

	virtual bool GetIsStale_Implementation() override;

	virtual bool GetShouldSendCoT_Implementation() override;

	virtual AUDPSender* GetUDPSender_Implementation() override;

	virtual ECotAffiliation GetAffiliation_Implementation() override;

	virtual void SetType_Implementation(FString& NewType) override;

	virtual void SetUid_Implementation(FString& NewUid) override;

	virtual void SetCallsign_Implementation(FString& NewCallsign) override;

	virtual void SetUDPSender_Implementation(AUDPSender* UdpSender) override;

	virtual void SetShouldSendCoT_Implementation(bool NewShouldSendCoT) override;

	virtual void SetAffiliation_Implementation(ECotAffiliation affiliation) override;
};
