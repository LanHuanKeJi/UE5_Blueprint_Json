// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value.h"
#include "NumberValue.generated.h"

/**
 * 
 */
UCLASS()
class MYJSON_API UNumberValue : public UValue
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "NumberValue")
	void SetValue(double InValue)
	{
		Value = InValue;
	}

	double GetValue()
	{
		return Value;
	}

	virtual FString ToString() override
	{
		return FString::SanitizeFloat(Value);
	}
private:
	double Value;
};
