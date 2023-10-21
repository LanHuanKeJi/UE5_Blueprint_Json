// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value.h"
#include "ArrayValue.generated.h"

/**
 * 
 */
UCLASS()
class MYJSON_API UArrayValue : public UValue
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "ArrayValue")
	void SetValue(TArray<UValue*> InValue)
	{
		Values = InValue;
	}

	TArray<UValue*> GetValue()
	{
		return Values;
	}

	virtual FString ToString() override
	{ 
		FString Result =  FString("[");

		for (int32 Index = 0; Index < Values.Num(); Index++)
		{
			UValue* Value = Values[Index];
			Result += Value->ToString();

			Result += ",";
		}

		if(Values.Num() > 0)
			Result = Result.LeftChop(1);

		Result += FString("]");

		return Result;
	}

	void Append(UValue* InValue)
	{
		Values.Push(InValue);
	}
private:
	TArray<UValue*> Values;
};
