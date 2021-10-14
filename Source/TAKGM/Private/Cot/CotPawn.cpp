// Fill out your copyright notice in the Description page of Project Settings.


#include "Cot/CotPawn.h"

// Forward declaration in header file -> include here
#include "UDP/UDPSender.h" 

// Sets default values
ACotPawn::ACotPawn()
{
	// Set this Pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// TODO: Generate unique Uid, remove hard-coded PLI
	Type = FString(TEXT("a-x-G"));
	Uid = this->GetUid_Implementation();
	Callsign = this->GetCallsign_Implementation();
	isStale = false;
	ShouldSendCoT = true;
	Affiliation = ECotAffiliation::AFFIL_Hostile;

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
		singletonUDPSender->SetStaleToNow(AUDPSender::FormTypeString(this), ICotSharable::Execute_GetUid(this), ICotSharable::Execute_GetCallsign(this), this->GetActorLocation());
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
	FVector longLatHeight = singletonUDPSender->transformUECoordToRealCoord(this->GetActorLocation());
	return longLatHeight.Y;
}

float ACotPawn::GetLongitude_Implementation()
{
	FVector longLatHeight = singletonUDPSender->transformUECoordToRealCoord(this->GetActorLocation());
	return longLatHeight.X;
}

float ACotPawn::GetHae_Implementation()
{
	FVector longLatHeight = singletonUDPSender->transformUECoordToRealCoord(this->GetActorLocation());
	return longLatHeight.Z;
}

bool ACotPawn::GetIsStale_Implementation()
{
	return isStale;
}

AUDPSender* ACotPawn::GetUDPSender_Implementation()
{
	return singletonUDPSender;
}

bool ACotPawn::GetShouldSendCoT_Implementation()
{
	return ShouldSendCoT;
}

ECotAffiliation ACotPawn::GetAffiliation_Implementation()
{
	return Affiliation;
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

void ACotPawn::SetUDPSender_Implementation(AUDPSender* UdpSender)
{
	singletonUDPSender = UdpSender;
}

void ACotPawn::SetShouldSendCoT_Implementation(bool NewShouldSendCoT)
{
	ShouldSendCoT = NewShouldSendCoT;
}

void ACotPawn::SetAffiliation_Implementation(ECotAffiliation affiliation)
{
	Affiliation = affiliation;
}