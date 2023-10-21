// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value.h"
#include "ObjectValue.generated.h"

/**
 * 
 */
UCLASS()
class MYJSON_API UObjectValue : public UValue
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "ObjectValue")
	void SetValue(TMap<FString, UValue*> InValue)
	{
		KeyValues = InValue;
	}

	virtual FString ToString() override
	{
		FString Result = FString("{");

		for (const TPair<FString,UValue*>& KeyValue : KeyValues)
		{
			Result += "\"";
			Result += KeyValue.Key;
			Result += "\":";
			Result += KeyValue.Value->ToString();

			Result += ",";
		}

		Result = Result.LeftChop(1);

		Result += FString("}");

		return Result;
	}

	void Set(const FString& InKey, UValue* InValue)
	{
		KeyValues.Add(InKey, InValue);
	}

	UValue* GetValueByKey(const FString& InKey)
	{
		if (KeyValues.Contains(InKey))
		{
			return KeyValues[InKey];
		}
		else
			return nullptr;
	}
private:
	TMap<FString, UValue*> KeyValues;
};
