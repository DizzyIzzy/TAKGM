// Fill out your copyright notice in the Description page of Project Settings.


#include "Cot/CotCharacter.h"

// Sets default values
ACotCharacter::ACotCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TODO: Generate unique Uid, remove hard-coded PLI
	Type = FString(TEXT("a-x-G"));
	Uid = this->GetUid_Implementation();
	Callsign = this->GetCallsign_Implementation();
	Latitude = 29.557232f;
	Longitude = -81.204465f;
	Hae = 10.0f;
	Ce = 1.0f;
	Le = 0.0f; 
	isStale = false;
	ShouldSendCoT = true;

	singletonUDPSender = (AUDPSender*)UGameplayStatics::GetActorOfClass(GetWorld(),
		AUDPSender::StaticClass());
}

// Called when the game starts or when spawned
void ACotCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACotCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (singletonUDPSender && EndPlayReason == EEndPlayReason::Type::Destroyed) {
		singletonUDPSender->SetStaleToNow(ICotSharable::Execute_GetType(this), ICotSharable::Execute_GetUid(this), ICotSharable::Execute_GetCallsign(this), this->GetActorLocation());
	}
	Super::EndPlay(EndPlayReason);
}

// Called to bind functionality to input
void ACotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FString ACotCharacter::GetType_Implementation()
{
	return Type;
}

FString ACotCharacter::GetUid_Implementation()
{
	return UKismetSystemLibrary::GetObjectName(this);
}

FString ACotCharacter::GetCallsign_Implementation()
{
	return UKismetSystemLibrary::GetObjectName(this);
}

float ACotCharacter::GetLatitude_Implementation()
{
	return Latitude;
}

float ACotCharacter::GetLongitude_Implementation()
{
	return Longitude;
}

float ACotCharacter::GetHae_Implementation()
{
	return Hae;
}

float ACotCharacter::GetCe_Implementation()
{
	return Ce;
}

bool ACotCharacter::GetIsStale_Implementation()
{
	return isStale;
}


float ACotCharacter::GetLe_Implementation()
{
	return Le;
}

AUDPSender* ACotCharacter::GetUDPSender_Implementation()
{
	return singletonUDPSender;
}

bool ACotCharacter::GetShouldSendCoT_Implementation()
{
	return ShouldSendCoT;
}

void ACotCharacter::SetType_Implementation(FString& NewType)
{
	Type = NewType;
}

void ACotCharacter::SetUid_Implementation(FString& NewUid)
{
	Uid = NewUid;
}

void ACotCharacter::SetCallsign_Implementation(FString& NewCallsign)
{
	Callsign = NewCallsign;
}

void ACotCharacter::SetLatitude_Implementation(float NewLatitude)
{
	Latitude = NewLatitude;
}

void ACotCharacter::SetLongitude_Implementation(float NewLongitude)
{
	Longitude = NewLongitude;
}

void ACotCharacter::SetHae_Implementation(float NewHae)
{
	Hae = NewHae;
}

void ACotCharacter::SetCe_Implementation(float NewCe)
{
	Ce = NewCe;
}

void ACotCharacter::SetLe_Implementation(float NewLe)
{
	Le = NewLe;
}

void ACotCharacter::SetUDPSender_Implementation(AUDPSender* UdpSender)
{
	singletonUDPSender = UdpSender;
}

void ACotCharacter::SetShouldSendCoT_Implementation(bool NewShouldSendCoT)
{
	ShouldSendCoT = NewShouldSendCoT;
}