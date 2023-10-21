// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Value.h"
#include "MyJsonBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UMyJsonBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Number Value", Keywords = "Make Number Value"), Category = "MyJson")
	static UValue* MakeNumberValue(double InNumber);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Boolean Value", Keywords = "Make Boolean Value"), Category = "MyJson")
	static UValue* MakeBooleanValue(bool bInBoolean);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make String Value", Keywords = "Make String Value"), Category = "MyJson")
	static UValue* MakeStringValue(FString InString);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Null Value", Keywords = "Make Null Value"), Category = "MyJson")
	static UValue* MakeNullValue();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Object Value", Keywords = "Make Object Value"), Category = "MyJson")
	static UValue* MakeObjectValue(TMap<FString, UValue* > InKeyValue);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Array Value", Keywords = "Make Array Value"), Category = "MyJson")
	static UValue* MakeArrayValue(TArray<UValue*> InValues);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Parse Value", Keywords = "Parse Value"), Category = "MyJson")
	static UValue* ParseValue(FString InString);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get String Value", Keywords = "Get String Value"), Category = "MyJson")
	static FString GetStringValue(UValue* InValue, const FString& InKey, bool& bSuccess);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Number Value", Keywords = "Get Number Value"), Category = "MyJson")
	static double GetNumberValue(UValue* InValue, const FString& InKey, bool& bSuccess);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Boolean Value", Keywords = "Get Boolean Value"), Category = "MyJson")
	static bool GetBooleanValue(UValue* InValue, const FString& InKey, bool& bSuccess);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Value", Keywords = "Get Object Value"), Category = "MyJson")
	static UValue* GetObjectValue(UValue* InValue, const FString& InKey, bool& bSuccess);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Array Value", Keywords = "Get Array Value"), Category = "MyJson")
	static TArray<UValue*> GetArrayValue(UValue* InValue, const FString& InKey, bool& bSuccess);
};
