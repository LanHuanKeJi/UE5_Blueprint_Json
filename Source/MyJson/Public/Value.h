// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Value.generated.h"

/**
 * 
 */
UCLASS()
class MYJSON_API UValue : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Value")
	virtual FString ToString() { return FString(""); }
};
 
