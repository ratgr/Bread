#pragma once
#include <cstdint>
#include <algorithm>




template<class TokenInfo>
struct BaseToken {
	enum TokenType : int16_t {
		EmptyToken = 0x00,
		String = 0x01,
		Identifier = 0x02,

		Separator = 0x40,
		Space = Separator + 0x01,
		EndLine = Separator + 0x02,

		Symbol = 0x0100,
		LParen, RParen,
		LBracket, RBracket,
		LCurly, RCurly,

		SymbolPlus,
		SymbolMinus,
		SymbolSlash,
		SymbolDoubleSlash,

		BitwiseOr,
		BitwiseAnd,
		BitwiseNot,
		BitwiseXor,
		BitwiseLShift,
		BitwiseRShift,

		LogicalEquals,
		LogicalAnd,
		LogicalOr,
		LogicalXor,

		GreaterThan,
		LessThan,
		NotEquals,
		GreaterEquals,

		Arrow,
	} tokenType;
	TokenInfo begin;
	TokenInfo end;
};



constexpr auto getSymbols() {
	TokenToCategory tokens[] = {
		{Token::Symbol,  "{"},
	};

	

}

const std::vector<TokenToCategory> Symbols = {

	{Token::Symbol,  "{"},
	{Token::Symbol,  "}"},
	{Token::Symbol,  "("},
	{Token::Symbol,  ")"},
	{Token::Symbol,  "["},
	{Token::Symbol,  "]"},
	{Token::Symbol,  "<"},
	{Token::Symbol,  ">"},

	{Token::Symbol,  "?"},
	{Token::Symbol,  "!"},

	{Token::SymbolPlus,  "+"},
	{Token::Symbol,  "-"},
	{Token::Symbol,  "*"},
	{Token::Symbol,  "/"},
	{Token::Symbol,  "@"},
	{Token::Symbol,  "="},
	{Token::Symbol,  "#"},
	{Token::Symbol,  "$"},
	{Token::Symbol,  "^"},
	{Token::Symbol,  "&"},
	{Token::Symbol,  "~"},
	{Token::Symbol,  "|"},
	{Token::Symbol,  ","},
	{Token::Symbol,  ";"},

	{Token::Symbol,  "->"},
	{Token::Symbol,  "=>"},
	{Token::Symbol,  "~>"},
};