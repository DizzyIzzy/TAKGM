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
		float Latitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		float Longitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		float Hae;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		float Ce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cot Sharable")
		float Le;

	// Sets default values for this character's properties
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

	virtual float GetLatitude_Implementation() override;

	virtual float GetLongitude_Implementation() override;

	virtual float GetHae_Implementation() override;

	virtual float GetCe_Implementation() override;

	virtual float GetLe_Implementation() override;
};
