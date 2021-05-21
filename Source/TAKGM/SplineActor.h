// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineActor.generated.h"




UCLASS()
class TAKGM_API ASplineActor : public AActor
{
	GENERATED_UCLASS_BODY()
private:

	UPROPERTY(Category = SplineActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|StaticMesh,Components|SplineMesh", AllowPrivateAccess = "true"))
		class USplineComponent* SplineMeshComponent;

public:	
	// Sets default values for this actor's properties
	ASplineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns SplineComponent subobject **/
	class USplineComponent* GetSplineComponent() const;

};
