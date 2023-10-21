// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Token.h"
#include "Lexer.generated.h"

/**
 * 词法分析器
 */
UCLASS()
class MYJSON_API ULexer : public UObject
{
	GENERATED_BODY()
public:
	Token GetNextToken() {
		while (Pos < Text.Len()) {
			TCHAR CurrentChar = Text[Pos];

			if (CurrentChar == '{') {
				Pos++;
				return Token{ TokenType::LEFT_BRACE, "{" };
			}
			else if (CurrentChar == '}') {
				Pos++;
				return Token{ TokenType::RIGHT_BRACE, "}" };
			}
			else if (CurrentChar == '[') {
				Pos++;
				return Token{ TokenType::LEFT_SQUARE_BRACKET, "[" };
			}
			else if (CurrentChar == ']') {
				Pos++;
				return Token{ TokenType::RIGHT_SQUARE_BRACKET, "]" };
			}
			else if (CurrentChar == ',') {
				Pos++;
				return Token{ TokenType::COMMA, "," };
			}
			else if (CurrentChar == ':') {
				Pos++;
				return Token{ TokenType::COLON, ":" };
			}
			else if (CurrentChar == '\"') {
				return GetStringToken();
			}
			else if (FChar::IsDigit(CurrentChar) || CurrentChar == '-') {
				return GetNumberToken();
			}
			else if (FChar::IsAlpha(CurrentChar)) {
				// 处理true/false/null
				FString Word;
				while (Pos < Text.Len() && FChar::IsAlpha(Text[Pos])) {
					Word += Text[Pos];
					Pos++;
				}

				if (Word == "true") {
					return Token{ TokenType::TRUE, "true" };
				}
				else if (Word == "false") {
					return Token{ TokenType::FALSE, "false" };
				}
				else if (Word == "null") {
					return Token{ TokenType::NULL_VALUE, "null" };
				}
				else {
					UE_LOG(LogTemp, Error, TEXT("Unexpected word: %s"), *Word);
					Pos++;
				}
			}
			else {
				Pos++;
			}
		}

		return Token{ TokenType::NULL_VALUE, "" };
	}

	void SetText(const FString& InText)
	{
		Text = InText;
		Pos = 0;
	}
private:
	FString Text = FString("");
	int32 Pos = 0;

	Token GetStringToken() {
		FString Value;
		Pos++;

		while (Pos < Text.Len()) {
			TCHAR CurrentChar = Text[Pos];

			if (CurrentChar == '\"') {
				Pos++;
				return Token{ TokenType::STRING, Value };
			}
			else if (CurrentChar == '\\') {
				// 处理转义字符
				if (Pos + 1 < Text.Len()) {
					TCHAR NextChar = Text[Pos + 1];
					if (NextChar == '\"' || NextChar == '\\' || NextChar == '/' || NextChar == 'b' || NextChar == 'f' || NextChar == 'n' || NextChar == 'r' || NextChar == 't') {
						Pos += 2;
						switch (NextChar) {
						case '\"':
							Value += '\"';
							break;
						case '\\':
							Value += '\\';
							break;
						case '/':
							Value += '/';
							break;
						case 'b':
							Value += '\b';
							break;
						case 'f':
							Value += '\f';
							break;
						case 'n':
							Value += '\n';
							break;
						case 'r':
							Value += '\r';
							break;
						case 't':
							Value += '\t';
							break;
						}
					}
					else {
						// 不支持的转义字符
						UE_LOG(LogTemp, Error, TEXT("Unexpected escape character: \\%c"),NextChar);
						Pos++;
					}
				}
				else {
					// 不完整的转义字符
					UE_LOG(LogTemp, Error, TEXT("Incomplete escape character"));
					Pos++;
				}
			}
			else {
				Value += CurrentChar;
				Pos++;
			}
		}

		return Token{ TokenType::NULL_VALUE, "" };
	}

	Token GetNumberToken() {
		FString Value;
		bool bIsNegative = false;

		if (Text[Pos] == '-') {
			bIsNegative = true;
			Pos++;
		}

		while (Pos < Text.Len() && FChar::IsDigit(Text[Pos])) {
			Value += Text[Pos];
			Pos++;
		}

		if (Pos < Text.Len() && Text[Pos] == '.') {
			// 处理小数部分
			Value += '.';
			Pos++;

			while (Pos < Text.Len() && FChar::IsDigit(Text[Pos])) {
				Value += Text[Pos];
				Pos++;
			}
		}

		if (Pos < Text.Len() && (Text[Pos] == 'e' || Text[Pos] == 'E')) {
			// 处理科学计数法部分
			Value += 'e';
			Pos++;

			if (Pos < Text.Len() && (Text[Pos] == '+' || Text[Pos] == '-')) {
				Value += Text[Pos];
				Pos++;
			}

			while (Pos < Text.Len() && FChar::IsDigit(Text[Pos])) {
				Value += Text[Pos];
				Pos++;
			}
		}

		if (bIsNegative) {
			return Token{ TokenType::NUMBER, FString("-") + Value };
		}
		else {
			return Token{ TokenType::NUMBER, Value };
		}
	}
};
