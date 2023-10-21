// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Value.h"
#include "ArrayValue.h"
#include "BooleanValue.h"
#include "NullValue.h"
#include "NumberValue.h"
#include "ObjectValue.h"
#include "StringValue.h"
#include "Lexer.h"
#include "Token.h"
#include "Parser.generated.h"


/**
 * Óï·¨·ÖÎöÆ÷
 */
UCLASS()
class MYJSON_API UParser : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UValue* Parse(FString InText)
	{
		Lexer->SetText(InText);
		CurrentToken = Lexer->GetNextToken();
		return ParseValue();
	}
private:
	ULexer* Lexer;
	Token CurrentToken;

	void Eat(TokenType InExpectedType) {
		if (CurrentToken.Type == InExpectedType) {
			CurrentToken = Lexer->GetNextToken();
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Syntax error: unexpected token %s"), *CurrentToken.Value);
		}
	}

	UValue* ParseValue() {
		switch (CurrentToken.Type) {
		case TokenType::LEFT_BRACE:
			return ParseObject();
		case TokenType::LEFT_SQUARE_BRACKET:
			return ParseArray();
		case TokenType::STRING:
			return ParseString();
		case TokenType::NUMBER:
			return ParseNumber();
		case TokenType::TRUE:
			return ParseTrue();
		case TokenType::FALSE:
			return ParseFalse();
		case TokenType::NULL_VALUE:
			return ParseNull();
		default:
			UE_LOG(LogTemp, Error, TEXT("Syntax error: unexpected token %s"), *CurrentToken.Value);
			return nullptr;
		}
	}

	UObjectValue* ParseObject() {
		Eat(TokenType::LEFT_BRACE);

		UObjectValue* ObjectValue = NewObject<UObjectValue>();

		while (CurrentToken.Type != TokenType::RIGHT_BRACE) {
			const FString& Key = ParseString()->GetValue();
			Eat(TokenType::COLON);
			UValue* Value = ParseValue();

			ObjectValue->Set(Key, Value);

			if (CurrentToken.Type == TokenType::COMMA) {
				Eat(TokenType::COMMA);
			}
			else if (CurrentToken.Type != TokenType::RIGHT_BRACE) {
				UE_LOG(LogTemp, Error, TEXT("Syntax error: unexpected token %s"), *CurrentToken.Value);
				break;
			}
		}

		Eat(TokenType::RIGHT_BRACE);

		return ObjectValue;
	}

	UArrayValue* ParseArray() {
		Eat(TokenType::LEFT_SQUARE_BRACKET);

		UArrayValue* ArrayValue = NewObject<UArrayValue>();

		while (CurrentToken.Type != TokenType::RIGHT_SQUARE_BRACKET) {
			auto value = ParseValue();
			ArrayValue->Append(value);

			if (CurrentToken.Type == TokenType::COMMA) {
				Eat(TokenType::COMMA);
			}
			else if (CurrentToken.Type != TokenType::RIGHT_SQUARE_BRACKET) {
				UE_LOG(LogTemp, Error, TEXT("Syntax error: unexpected token %s"), *CurrentToken.Value);
				break;
			}
		}
		Eat(TokenType::RIGHT_SQUARE_BRACKET);

		return ArrayValue;
	}

	UStringValue* ParseString() {
		UStringValue* StringValue = NewObject<UStringValue>();
		StringValue->SetValue(CurrentToken.Value);
		Eat(TokenType::STRING);
		return StringValue;
	}

	UNumberValue* ParseNumber() {
		double Value = FCString::Atof(*CurrentToken.Value);
		Eat(TokenType::NUMBER);
		UNumberValue* NumberValue = NewObject<UNumberValue>();
		NumberValue->SetValue(Value);
		return NumberValue;
	}

	UBooleanValue* ParseTrue() {
		Eat(TokenType::TRUE);
		UBooleanValue* BooleanValue = NewObject<UBooleanValue>();
		BooleanValue->SetValue(true);
		return BooleanValue;
	}

	UBooleanValue* ParseFalse() {
		Eat(TokenType::FALSE);
		UBooleanValue* BooleanValue = NewObject<UBooleanValue>();
		BooleanValue->SetValue(false);
		return BooleanValue;
	}

	UNullValue* ParseNull() {
		Eat(TokenType::NULL_VALUE);
		UNullValue* NullValue = NewObject<UNullValue>();
		return NullValue;
	}
};
