// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineActor.h"
#include "Components/SplineComponent.h"
// Sets default values
ASplineActor::ASplineActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SplineMeshComponent = ObjectInitializer.CreateDefaultSubobject<USplineComponent>(this, TEXT("SplineMeshComponent0"));
	SplineMeshComponent->Mobility = EComponentMobility::Static;
	SplineMeshComponent->SetGenerateOverlapEvents(false);

}

// Called when the game starts or when spawned
void ASplineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplineActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

USplineComponent* ASplineActor::GetSplineComponent() const
{
	return SplineMeshComponent;
}

