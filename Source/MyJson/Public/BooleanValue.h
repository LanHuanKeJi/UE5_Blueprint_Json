// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value.h"
#include "BooleanValue.generated.h"

/**
 * 
 */
UCLASS()
class MYJSON_API UBooleanValue : public UValue
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "BooleanValue")
	void SetValue(bool bInValue)
	{
		bValue = bInValue;
	}

	bool GetValue()
	{
		return bValue;
	}

	virtual FString ToString() override
	{
		return bValue ? "true":"false";
	}
private:
	bool bValue = false;
};
