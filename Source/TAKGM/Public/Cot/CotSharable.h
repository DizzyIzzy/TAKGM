// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CotSharable.generated.h"

UENUM(BlueprintType)
enum class ECotAffiliation : uint8
{
	AFFIL_Friendly     UMETA(DisplayName = "Friendly"),
	AFFIL_Hostile      UMETA(DisplayName = "Hostile"),
	AFFIL_Neutral   UMETA(DisplayName = "Neutral"),
	AFFIL_Other		UMETA(DisplayName = "Other"),
};

UINTERFACE(MinimalAPI)
class UCotSharable : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class TAKGM_API ICotSharable
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		FString GetType();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		FString GetUid();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		FString GetCallsign();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		float GetLatitude();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		float GetLongitude();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		float GetHae();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		float GetCe();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		float GetLe();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		bool GetIsStale();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		AUDPSender* GetUDPSender();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		bool GetShouldSendCoT();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		ECotAffiliation GetAffiliation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity", meta = (AdvancedDisplay = 1))
		void SetType(UPARAM(ref, DisplayName = "Type") FString& NewType);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		void SetUid(UPARAM(ref, DisplayName = "UID") FString& NewUid);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		void SetCallsign(UPARAM(ref, DisplayName = "Callsign") FString& NewCallsign);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		void SetLatitude(UPARAM(DisplayName = "Latitude") float NewLatitude);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		void SetLongitude(UPARAM(DisplayName = "Longitude") float NewLongitude);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		void SetHae(UPARAM(DisplayName = "HAE (Height Above Ellipsoid") float NewHae);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		void SetCe(UPARAM(DisplayName = "CE") float NewCe);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		void SetLe(UPARAM(DisplayName = "LE") float NewLe);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		void SetUDPSender(UPARAM(DisplayName = "UDP Sender Reference") AUDPSender* UdpSender);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		void SetShouldSendCoT(UPARAM(DisplayName = "Should Send CoT") bool shouldSendCoT);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Cot Entity")
		void SetAffiliation(UPARAM(DisplayName = "Affiliation (friend/hostile/neutral)") ECotAffiliation affiliation);
};
