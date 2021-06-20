// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CotSharable.h"
#include "CotCharacter.generated.h"

UCLASS()
class TAKGM_API ACotCharacter : public ACharacter, public ICotSharable
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
		float Latitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		float Longitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		float Hae;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		float Ce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		float Le;

	// Constructor
	ACotCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Implements functions from ICotSharable
	virtual FString GetType_Implementation() override;

	virtual FString GetUid_Implementation() override;

	virtual FString GetCallsign_Implementation() override;

	virtual float GetLatitude_Implementation() override;

	virtual float GetLongitude_Implementation() override;

	virtual float GetHae_Implementation() override;

	virtual float GetCe_Implementation() override;

	virtual float GetLe_Implementation() override;

	virtual void SetType_Implementation(FString& NewType) override;

	virtual void SetUid_Implementation(FString& NewUid) override;

	virtual void SetCallsign_Implementation(FString& NewCallsign) override;

	virtual void SetLatitude_Implementation(float NewLatitude) override;

	virtual void SetLongitude_Implementation(float NewLongitude) override;

	virtual void SetHae_Implementation(float NewHae) override;

	virtual void SetCe_Implementation(float NewCe) override;

	virtual void SetLe_Implementation(float NewLe) override;
};
