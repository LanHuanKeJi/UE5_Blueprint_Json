// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyJsonBPLibrary.h"
#include "MyJson.h"
#include "NumberValue.h"
#include "StringValue.h"
#include "BooleanValue.h"
#include "NullValue.h"
#include "ObjectValue.h"
#include "ArrayValue.h"
#include "Parser.h"

UMyJsonBPLibrary::UMyJsonBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

UValue* UMyJsonBPLibrary::MakeNumberValue(double InNumber)
{
	UNumberValue* Value = NewObject<UNumberValue>();
	Value->SetValue(InNumber);
	return Value;
}

UValue* UMyJsonBPLibrary::MakeBooleanValue(bool bInBoolean)
{
	UBooleanValue* Value = NewObject<UBooleanValue>();
	Value->SetValue(bInBoolean);
	return Value;
}

UValue* UMyJsonBPLibrary::MakeStringValue(FString InString)
{
	UStringValue* Value = NewObject<UStringValue>();
	Value->SetValue(InString);
	return Value;
}

UValue* UMyJsonBPLibrary::MakeNullValue()
{
	UNullValue* Value = NewObject<UNullValue>();
	return Value;
}

UValue* UMyJsonBPLibrary::MakeObjectValue(TMap<FString, UValue*> InKeyValues)
{
	UObjectValue* Value = NewObject<UObjectValue>();
	Value->SetValue(InKeyValues);
	return Value;
}

UValue* UMyJsonBPLibrary::MakeArrayValue(TArray<UValue*> InValues)
{
	UArrayValue* Value = NewObject<UArrayValue>();
	Value->SetValue(InValues);
	return Value;
}

UValue* UMyJsonBPLibrary::ParseObjectValue(FString InString)
{
	UParser* Parser = NewObject<UParser>();
	return Parser->Parse(InString);
}

TArray<UValue*> UMyJsonBPLibrary::ParseArrayValue(FString InString)
{
	UParser* Parser = NewObject<UParser>();
	UValue* Value = Parser->Parse(InString);
	UArrayValue* ArrayValue = Cast<UArrayValue>(Value);
	if (!IsValid(ArrayValue))
	{
		return TArray<UValue*>();
	}

	return ArrayValue->GetValue();
}

FString UMyJsonBPLibrary::GetStringValue(UValue* InValue, const FString& InKey,bool& bSuccess)
{
	if (!IsValid(InValue))
	{
		bSuccess = false;
		return "";
	}

	UObjectValue* ObjectValue = Cast<UObjectValue>(InValue);
	if (!IsValid(ObjectValue))
	{
		bSuccess = false;
		return "";
	}

	UValue* Value = ObjectValue->GetValueByKey(InKey);
	if (!IsValid(Value))
	{
		bSuccess = false;
		return "";
	}

	UStringValue* StringValue = Cast<UStringValue>(Value);
	if (!IsValid(StringValue))
	{
		bSuccess = false;
		return "";
	}

	bSuccess = true;
	return StringValue->GetValue();
}

double UMyJsonBPLibrary::GetNumberValue(UValue* InValue, const FString& InKey, bool& bSuccess)
{
	if (!IsValid(InValue))
	{
		bSuccess = false;
		return 0;
	}

	UObjectValue* ObjectValue = Cast<UObjectValue>(InValue);
	if (!IsValid(ObjectValue))
	{
		bSuccess = false;
		return 0;
	}

	UValue* Value = ObjectValue->GetValueByKey(InKey);
	if (!IsValid(Value))
	{
		bSuccess = false;
		return 0;
	}

	UNumberValue* NumberValue = Cast<UNumberValue>(Value);
	if (!IsValid(NumberValue))
	{
		bSuccess = false;
		return 0;
	}

	bSuccess = true;
	return NumberValue->GetValue();
}

bool UMyJsonBPLibrary::GetBooleanValue(UValue* InValue, const FString& InKey, bool& bSuccess)
{
	if (!IsValid(InValue))
	{
		bSuccess = false;
		return 0;
	}

	UObjectValue* ObjectValue = Cast<UObjectValue>(InValue);
	if (!IsValid(ObjectValue))
	{
		bSuccess = false;
		return 0;
	}

	UValue* Value = ObjectValue->GetValueByKey(InKey);
	if (!IsValid(Value))
	{
		bSuccess = false;
		return 0;
	}

	UBooleanValue* BooleanValue = Cast<UBooleanValue>(Value);
	if (!IsValid(BooleanValue))
	{
		bSuccess = false;
		return 0;
	}

	bSuccess = true;
	return BooleanValue->GetValue();
}

UValue* UMyJsonBPLibrary::GetObjectValue(UValue* InValue, const FString& InKey, bool& bSuccess)
{
	if (!IsValid(InValue))
	{
		bSuccess = false;
		return nullptr;
	}

	UObjectValue* ObjectValue = Cast<UObjectValue>(InValue);
	if (!IsValid(ObjectValue))
	{
		bSuccess = false;
		return nullptr;
	}

	UValue* Value = ObjectValue->GetValueByKey(InKey);
	if (!IsValid(Value))
	{
		bSuccess = false;
		return nullptr;
	}

	bSuccess = true;
	return Value;
}

TArray<UValue*> UMyJsonBPLibrary::GetArrayValue(UValue* InValue, const FString& InKey, bool& bSuccess)
{
	if(!IsValid(InValue))
	{
		bSuccess = false;
		return TArray<UValue*>();
	}

	UObjectValue* ObjectValue = Cast<UObjectValue>(InValue);
	if (!IsValid(ObjectValue))
	{
		bSuccess = false;
		return TArray<UValue*>();
	}

	UValue* Value = ObjectValue->GetValueByKey(InKey);
	if (!IsValid(Value))
	{
		bSuccess = false;
		return TArray<UValue*>();
	}

	UArrayValue* ArrayValue = Cast<UArrayValue>(Value);
	if (!IsValid(ArrayValue))
	{
		bSuccess = false;
		return TArray<UValue*>();
	}

	bSuccess = true;
	return ArrayValue->GetValue();
}
