// Fill out your copyright notice in the Description page of Project Settings.


#include "Cot/CotPawn.h"

// Sets default values
ACotPawn::ACotPawn()
{
	// Set this Pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
void ACotPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACotPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACotPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (singletonUDPSender && EndPlayReason == EEndPlayReason::Type::Destroyed) {
		singletonUDPSender->SetStaleToNow(ICotSharable::Execute_GetType(this), ICotSharable::Execute_GetUid(this), ICotSharable::Execute_GetCallsign(this), this->GetActorLocation());
	}
	Super::EndPlay(EndPlayReason);
}

// Called to bind functionality to input
void ACotPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FString ACotPawn::GetType_Implementation()
{
	return Type;
}

FString ACotPawn::GetUid_Implementation()
{
	return UKismetSystemLibrary::GetObjectName(this);
}

FString ACotPawn::GetCallsign_Implementation()
{
	return UKismetSystemLibrary::GetObjectName(this);
}

float ACotPawn::GetLatitude_Implementation()
{
	return Latitude;
}

float ACotPawn::GetLongitude_Implementation()
{
	return Longitude;
}

float ACotPawn::GetHae_Implementation()
{
	return Hae;
}

float ACotPawn::GetCe_Implementation()
{
	return Ce;
}

bool ACotPawn::GetIsStale_Implementation()
{
	return isStale;
}

float ACotPawn::GetLe_Implementation()
{
	return Le;
}

AUDPSender* ACotPawn::GetUDPSender_Implementation()
{
	return singletonUDPSender;
}

bool ACotPawn::GetShouldSendCoT_Implementation()
{
	return ShouldSendCoT;
}

void ACotPawn::SetType_Implementation(FString& NewType)
{
	Type = NewType;
}

void ACotPawn::SetUid_Implementation(FString& NewUid)
{
	Uid = NewUid;
}

void ACotPawn::SetCallsign_Implementation(FString& NewCallsign)
{
	Callsign = NewCallsign;
}

void ACotPawn::SetLatitude_Implementation(float NewLatitude)
{
	Latitude = NewLatitude;
}

void ACotPawn::SetLongitude_Implementation(float NewLongitude)
{
	Longitude = NewLongitude;
}

void ACotPawn::SetHae_Implementation(float NewHae)
{
	Hae = NewHae;
}

void ACotPawn::SetCe_Implementation(float NewCe)
{
	Ce = NewCe;
}

void ACotPawn::SetLe_Implementation(float NewLe)
{
	Le = NewLe;
}

void ACotPawn::SetUDPSender_Implementation(AUDPSender* UdpSender)
{
	singletonUDPSender = UdpSender;
}

void ACotPawn::SetShouldSendCoT_Implementation(bool NewShouldSendCoT)
{
	ShouldSendCoT = NewShouldSendCoT;
}