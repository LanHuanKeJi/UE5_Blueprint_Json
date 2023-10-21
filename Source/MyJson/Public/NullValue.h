// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value.h"
#include "NullValue.generated.h"

/**
 * 
 */
UCLASS()
class MYJSON_API UNullValue : public UValue
{
	GENERATED_BODY()
public:
	virtual FString ToString() override
	{
		return "null";
	}
};
