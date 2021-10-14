// Fill out your copyright notice in the Description page of Project Settings.


#include "Cot/CotActor.h"

// Forward declaration in header file -> include here
#include "UDP/UDPSender.h"

// Sets default values
ACotActor::ACotActor()
{
	// Set this Actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TODO: Generate unique Uid, remove hard-coded PLI
	Type = FString(TEXT("a-x-G"));
	Uid = this->GetUid_Implementation();
	Callsign = this->GetCallsign_Implementation();
	isStale = false;
	ShouldSendCoT = true;
	Affiliation = ECotAffiliation::AFFIL_Hostile;

	singletonUDPSender = (AUDPSender *) UGameplayStatics::GetActorOfClass(GetWorld(),
		AUDPSender::StaticClass());

}

// Called when the game starts or when spawned
void ACotActor::BeginPlay()
{
	Super::BeginPlay();

}

void ACotActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (singletonUDPSender && EndPlayReason == EEndPlayReason::Type::Destroyed) {
		singletonUDPSender->SetStaleToNow(AUDPSender::FormTypeString(this), ICotSharable::Execute_GetUid(this), ICotSharable::Execute_GetCallsign(this), this->GetActorLocation());
	}
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ACotActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ACotActor::GetType_Implementation()
{
	return Type;
}

FString ACotActor::GetUid_Implementation()
{
	return UKismetSystemLibrary::GetObjectName(this);
}

FString ACotActor::GetCallsign_Implementation()
{
	return UKismetSystemLibrary::GetObjectName(this);
}

float ACotActor::GetLatitude_Implementation()
{
	FVector longLatHeight = singletonUDPSender->transformUECoordToRealCoord(this->GetActorLocation());
	return longLatHeight.Y;
}

float ACotActor::GetLongitude_Implementation()
{
	FVector longLatHeight = singletonUDPSender->transformUECoordToRealCoord(this->GetActorLocation());
	return longLatHeight.X;
}

float ACotActor::GetHae_Implementation()
{
	FVector longLatHeight = singletonUDPSender->transformUECoordToRealCoord(this->GetActorLocation());
	return longLatHeight.Z;
}

bool ACotActor::GetIsStale_Implementation()
{
	return isStale;
}

AUDPSender* ACotActor::GetUDPSender_Implementation()
{
	return singletonUDPSender;
}

bool ACotActor::GetShouldSendCoT_Implementation()
{
	return ShouldSendCoT;
}

ECotAffiliation ACotActor::GetAffiliation_Implementation()
{
	return Affiliation;
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

void ACotActor::SetUDPSender_Implementation(AUDPSender* UdpSender)
{
	singletonUDPSender = UdpSender;
}

void ACotActor::SetShouldSendCoT_Implementation(bool NewShouldSendCoT)
{
	ShouldSendCoT = NewShouldSendCoT;
}

void ACotActor::SetAffiliation_Implementation(ECotAffiliation affiliation)
{
	Affiliation = affiliation;
}