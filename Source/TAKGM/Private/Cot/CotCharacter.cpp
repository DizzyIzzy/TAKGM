// Fill out your copyright notice in the Description page of Project Settings.


#include "Cot/CotCharacter.h"

// Forward declaration in header file -> include here
#include "UDP/UDPSender.h"

// Sets default values
ACotCharacter::ACotCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
		singletonUDPSender->SetStaleToNow(AUDPSender::FormTypeString(this), ICotSharable::Execute_GetUid(this), ICotSharable::Execute_GetCallsign(this), this->GetActorLocation());
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
	FVector longLatHeight = singletonUDPSender->transformUECoordToRealCoord(this->GetActorLocation());
	return longLatHeight.Y;
}

float ACotCharacter::GetLongitude_Implementation()
{
	FVector longLatHeight = singletonUDPSender->transformUECoordToRealCoord(this->GetActorLocation());
	return longLatHeight.X;
}

float ACotCharacter::GetHae_Implementation()
{
	FVector longLatHeight = singletonUDPSender->transformUECoordToRealCoord(this->GetActorLocation());
	return longLatHeight.Z;
}

bool ACotCharacter::GetIsStale_Implementation()
{
	return isStale;
}

AUDPSender* ACotCharacter::GetUDPSender_Implementation()
{
	return singletonUDPSender;
}

bool ACotCharacter::GetShouldSendCoT_Implementation()
{
	return ShouldSendCoT;
}

ECotAffiliation ACotCharacter::GetAffiliation_Implementation()
{
	return Affiliation;
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

void ACotCharacter::SetUDPSender_Implementation(AUDPSender* UdpSender)
{
	singletonUDPSender = UdpSender;
}

void ACotCharacter::SetShouldSendCoT_Implementation(bool NewShouldSendCoT)
{
	ShouldSendCoT = NewShouldSendCoT;
}

void ACotCharacter::SetAffiliation_Implementation(ECotAffiliation affiliation)
{
	Affiliation = affiliation;
}