// Fill out your copyright notice in the Description page of Project Settings.


#include "Parser.h"

UParser::UParser(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Lexer = NewObject<ULexer>();
}