#pragma once

#include "CoreMinimal.h"

enum class TokenType {
	LEFT_BRACE,
	RIGHT_BRACE,
	LEFT_SQUARE_BRACKET,
	RIGHT_SQUARE_BRACKET,
	COMMA,
	COLON,
	STRING,
	NUMBER,
	TRUE,
	FALSE,
	NULL_VALUE
};

struct Token {
	TokenType Type;
	FString Value;
};