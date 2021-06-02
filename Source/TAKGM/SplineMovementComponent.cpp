// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineMovementComponent.h"
#include "Components/SplineComponent.h"
// Sets default values for this component's properties
USplineMovementComponent::USplineMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USplineMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}


// Called every frame
void USplineMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float DistanceTraveled = Speed * DeltaTime;
	if (CurrentDistanceAlongSpline < GoalDistanceAlongSpline)
	{
		CurrentDistanceAlongSpline += DistanceTraveled;
		FVector Location = SplineActor->GetSplineComponent()->GetLocationAtDistanceAlongSpline(CurrentDistanceAlongSpline,ESplineCoordinateSpace::World);
		FRotator Rotation = SplineActor->GetSplineComponent()->GetRotationAtDistanceAlongSpline(CurrentDistanceAlongSpline, ESplineCoordinateSpace::Local);
		GetOwner()->SetActorLocation(Location);
		GetOwner()->SetActorRotation(Rotation);
		//SplineActor->GetSplineComponent()->GetDistanceAlongSplineAtSplinePoint();
	}
	else
	{
		ArrivedAtPoint.Broadcast(GoalPoint);
		this->SetComponentTickEnabled(false);
	}
	
}

void USplineMovementComponent::Initialize(TArray<FVector> WayPoints)
{
	this->Waypoints = WayPoints;
	if (SplineActor)
		SplineActor->Destroy();
	SplineActor = GetWorld()->SpawnActor<ASplineActor>();
	SplineActor->SetActorLocation(GetOwner()->GetActorLocation());

	SplineActor->GetSplineComponent()->RemoveSplinePoint(0);

	if (WayPoints.Num())
	{
		SplineActor->SetActorLocation(WayPoints[0]);
	}
	SplineActor->GetSplineComponent()->SetSplinePoints(WayPoints,ESplineCoordinateSpace::World);
}

void USplineMovementComponent::TravelToWayPoint(int Point)
{
	GoalPoint = Point;
	if (!SplineActor) return;
	this->SetComponentTickEnabled(true);
	GoalDistanceAlongSpline = SplineActor->GetSplineComponent()->GetDistanceAlongSplineAtSplinePoint(Point);
}

void USplineMovementComponent::ProceedToNextPoint()
{
	GoalPoint++;
	this->SetComponentTickEnabled(true);
	GoalDistanceAlongSpline = SplineActor->GetSplineComponent()->GetDistanceAlongSplineAtSplinePoint(GoalPoint);
	//GoalDistanceAlongSpline
}

float USplineMovementComponent::GetLengthAlongSpline()
{
	return CurrentDistanceAlongSpline;
}

float USplineMovementComponent::GetSplineLength()
{
	if (SplineActor && SplineActor->GetSplineComponent())
	{
		return SplineActor->GetSplineComponent()->GetSplineLength();
	}
	return 0.0f;
}

