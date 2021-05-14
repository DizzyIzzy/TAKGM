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
		FRotator Rotation = SplineActor->GetSplineComponent()->GetRotationAtDistanceAlongSpline(CurrentDistanceAlongSpline, ESplineCoordinateSpace::World);
		GetOwner()->SetActorLocation(Location);
		GetOwner()->SetActorRotation(Rotation);
		//SplineActor->GetSplineComponent()->GetDistanceAlongSplineAtSplinePoint();
	}
	
}

void USplineMovementComponent::Initialize(TArray<FVector> WayPoints)
{
	this->Waypoints = WayPoints;
	if (SplineActor)
		SplineActor->Destroy();
	SplineActor = GetWorld()->SpawnActor<ASplineActor>();
	SplineActor->SetActorLocation(GetOwner()->GetActorLocation());

	if (WayPoints.Num())
	{
		SplineActor->SetActorLocation(WayPoints[0]);
	}
	SplineActor->GetSplineComponent()->RemoveSplinePoint(0);
	for (int i = 0; i < Waypoints.Num();i++)
	{
		//FSplinePoint Point = FSplinePoint(i, Waypoints[i], FVector(0,0,0), FVector::ZeroVector);
		//SplineActor->GetSplineComponent()->AddPoint(Point);
		SplineActor->GetSplineComponent()->AddSplineWorldPoint(Waypoints[i]);
		SplineActor->GetSplineComponent()->SetSplinePointType(i, ESplinePointType::CurveClamped);
	}
}

void USplineMovementComponent::TravelToWayPoint(int Point)
{
	GoalPoint = Point;
	if (!SplineActor) return;
	GoalDistanceAlongSpline = SplineActor->GetSplineComponent()->GetDistanceAlongSplineAtSplinePoint(Point);
}

void USplineMovementComponent::ProceedToNextPoint()
{
	GoalPoint++;

	GoalDistanceAlongSpline = SplineActor->GetSplineComponent()->GetDistanceAlongSplineAtSplinePoint(GoalPoint);
	//GoalDistanceAlongSpline
}

