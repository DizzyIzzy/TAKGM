#pragma once

#include "UDPData.generated.h"

USTRUCT(BlueprintType)
struct FUDPData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COT")
		FString CoTMessage = "<INSERT COT>";

	FUDPData()
	{}
};

FORCEINLINE FArchive& operator<<(FArchive& Ar, FUDPData& TheStruct)
{
	Ar << TheStruct.CoTMessage;

	return Ar;
}