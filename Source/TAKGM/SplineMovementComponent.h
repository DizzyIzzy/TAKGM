// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SplineActor.h"
#include "SplineMovementComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWayPointDelegate, int32, GoalPoint);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAKGM_API USplineMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USplineMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly)
		ASplineActor* SplineActor;

	//Speed in Cm/s
	UPROPERTY(EditanyWhere, BlueprintReadWrite)
		float Speed = 1000;

	UFUNCTION(BlueprintCallable)
		void Initialize(TArray<FVector> WayPoints);

	UFUNCTION(BlueprintCallable)
		void TravelToWayPoint(int Point);

	UFUNCTION(BlueprintCallable)
		void ProceedToNextPoint();



	UPROPERTY(BlueprintAssignable, Category = "Custom")
		FWayPointDelegate ArrivedAtPoint;

	UFUNCTION(BlueprintPure)
		float GetLengthAlongSpline();

	UFUNCTION(BlueprintPure)
		float GetSplineLength();


private:
	TArray<FVector> Waypoints;

	float CurrentDistanceAlongSpline = 0;
	float GoalDistanceAlongSpline = 0;
	int GoalPoint = 0;
};
