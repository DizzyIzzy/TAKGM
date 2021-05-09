// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CoTEntityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCoTEntityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TAKGM_API ICoTEntityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CoT Accessor")
		FString GetType();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CoT Accessor")
		FString GetUid();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CoT Accessor")
		float GetLatitude();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CoT Accessor")
		float GetLongitude();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CoT Accessor")
		float GetHae();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CoT Accessor")
		FString GetCe();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "CoT Accessor")
		FString GetLe();

};
