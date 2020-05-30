#pragma once
#include <optional>
#include <variant>
#include <functional>
#include "Tokenizer.hpp"


template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...)->overload<Ts...>;

template<class T, class TMatcher>
struct TokenMatcher {

	static constexpr auto AlwaysMatch = []() { return true; };

	//TMatcher -> bool (variant)
	TMatcher matcher;
	
	TokenMatcher(TMatcher matcher) : matcher{ matcher } {};

	auto operator[] (const char* c) {

		return ;
	}


};

template<class S>
static auto Match() {
	auto lamda = overload(
		[](const S&) {return true; },
		[](auto&&) {return false; }//
	);
	return TokenMatcher <std::tuple<S>, decltype(lamda)>(lamda);
};

void lex() {
	int row = 4;
	int column = 6;


	auto val = TokenParser::Tokenize("", row, column).value();
}

class MainLexer {

};



// Matcher<Token::Number>() -> (Token::Number)
// Matcher<Token::Identifier>().starts("user").


// if a > b {}


// Scope = Global
// opstack: []
// stack: []
// action: remove Token -> Token::If
// opstack: [if]
// stack [IdentifierA]


struct Statement;
struct IFStatement {};

