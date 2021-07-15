// Fill out your copyright notice in the Description page of Project Settings.


#include "Cot/CotActor.h"

// Sets default values
ACotActor::ACotActor()
{
	// Set this Actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TODO: Generate unique Uid, remove hard-coded PLI
	Type = FString(TEXT("a-x-G"));
	Uid = FString(TEXT("TAKBOT"));
	Callsign = FString(TEXT("Survivor"));
	Latitude = 29.557232f;
	Longitude = -81.204465f;
	Hae = 10.0f;
	Ce = 1.0f;
	Le = 0.0f;

}

// Called when the game starts or when spawned
void ACotActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACotActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/*
void ACotActor::BeginDestroy()
{
	if (singletonUDPSender) {
		singletonUDPSender->SetStaleToNow(this);
	}
	Super::BeginDestroy();
}*/

FString ACotActor::GetType_Implementation()
{
	return Type;
}

FString ACotActor::GetUid_Implementation()
{
	return Uid;
}

FString ACotActor::GetCallsign_Implementation()
{
	return Callsign;
}

float ACotActor::GetLatitude_Implementation()
{
	return Latitude;
}

float ACotActor::GetLongitude_Implementation()
{
	return Longitude;
}

float ACotActor::GetHae_Implementation()
{
	return Hae;
}

float ACotActor::GetCe_Implementation()
{
	return Ce;
}

float ACotActor::GetLe_Implementation()
{
	return Le;
}

AUDPSender* ACotActor::GetUDPSender_Implementation()
{
	return singletonUDPSender;
}

void ACotActor::SetType_Implementation(FString& NewType)
{
	Type = NewType;
}

void ACotActor::SetUid_Implementation(FString& NewUid)
{
	Uid = NewUid;
}

void ACotActor::SetCallsign_Implementation(FString& NewCallsign)
{
	Callsign = NewCallsign;
}

void ACotActor::SetLatitude_Implementation(float NewLatitude)
{
	Latitude = NewLatitude;
}

void ACotActor::SetLongitude_Implementation(float NewLongitude)
{
	Longitude = NewLongitude;
}

void ACotActor::SetHae_Implementation(float NewHae)
{
	Hae = NewHae;
}

void ACotActor::SetCe_Implementation(float NewCe)
{
	Ce = NewCe;
}

void ACotActor::SetLe_Implementation(float NewLe)
{
	Le = NewLe;
}

void ACotActor::SetUDPSender_Implementation(AUDPSender* UdpSender)
{
	singletonUDPSender = UdpSender;
}