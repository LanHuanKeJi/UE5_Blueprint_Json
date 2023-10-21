// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value.h"
#include "StringValue.generated.h"

/**
 * 
 */
UCLASS()
class MYJSON_API UStringValue : public UValue
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "StringValue")
	void SetValue(FString InValue)
	{
		Value = InValue;
	}

	virtual FString ToString() override
	{
		FString Result = FString("\"");
		Result += Value;
		Result += FString("\"");
		return Result;
	}

	const FString& GetValue() const
	{
		return Value;
	}
private:
	FString Value;
};
