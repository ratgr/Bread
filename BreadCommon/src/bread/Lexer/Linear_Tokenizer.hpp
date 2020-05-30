#pragma once
#include <string_view>
#include <map>
#include <unordered_map>
#include <optional>
#include <functional>
#include <cctype>
#include "Token.h"


struct Token;
enum Token::TokenType;

using TokenInfo = std::string_view::const_iterator;
using TokenAction = std::function<std::optional<Token> (TokenInfo)>;
using Token = BaseToken<TokenInfo>;

bool isEnd(TokenInfo info) {
	return *info == 0;
}




template<class T>
struct Tokenizer {
	T call;
	std::optional<Token> operator () (TokenInfo info) { return call(info); };
	Tokenizer(T callable) : call{ callable } {}


	template<class S>
	auto operator * (const Tokenizer<S>& other)
	{
		return Tokenizer{ [=](TokenInfo info) -> std::optional<Token> {
			auto tokenA = this->operator()(info);
			if (!tokenA.has_value()) return other.operator ()(info);
			auto tokenB = other.operator ()(tokenA->end);
			if (!tokenB.has_value()) return std::nullopt;
			tokenB->begin = tokenA->begin;
		} }

	}

	template<class S>
	auto operator + (const Tokenizer<S>& other)
	{
		return Tokenizer{[=] (TokenInfo info) -> std::optional<Token> {
			auto tokenA = this->operator()(info);
			if (!tokenA.has_value()) return std::nullopt;
			auto tokenB = other.operator ()(tokenA->end);
			if (!tokenB.has_value()) return std::nullopt;
			tokenB->begin = tokenA->begin;
		}}

	}

	auto opt ()
	{
		return Tokenizer{ [=](TokenInfo info) -> std::optional<Token> {
			auto tokenA = this->operator()(info);
			if (!tokenA.has_value()) return Token{ .tokenType=Token::EmptyToken, .begin=info, .end=info};
		} }

	}

};

bool startsWith(TokenInfo& info, const char* start) {
	for (; !isEnd(info) && *start != 0 && *info == *start; start++) {}
	return start == 0;
}

namespace Tokens {
	template<class TCallable>
	auto While(Token::TokenType tokenType, TCallable callable) {
		return Tokenizer{ [=](TokenInfo info) -> std::optional<Token> {
			auto begin = info;
			for (; (!isEnd(info) && callable(*info)); info++);
			if (info - begin > 0) {
				return Token{ tokenType, begin, info };
			}
			return std::nullopt;
		} };
	}
	auto Greedy(Token::TokenType tokenType, const char* start, const char* end, const char escaper = 0) {
		return Tokenizer{ [=](TokenInfo info) -> std::optional<Token> {
			if (!startsWith(info, start)) return std::nullopt;
			auto begin = info;
			for (; (!isEnd(info)); info++) {
				if (*info == escaper) { info++; continue; }
				auto endinfo = info;
				if (startsWith(endinfo, start)) return Token{ tokenType, begin, endinfo };;
			}
			return std::nullopt;
		} };
	}

	template<class TCallable>
	auto Match(Token::TokenType tokenType, const char * value) {
		return Tokenizer{ [=](TokenInfo info) -> std::optional<Token> {
			auto begin = info;
			if(startsWith(info, value)) return Token{ tokenType, begin, info };
			return std::nullopt;
		} };
	}

	auto Symbols(TokenInfo info) -> std::optional<Token> {
		
	}


}


//std::vector<std::tuple<Token,std::vector<char*>>>


struct TokenToCategory {
	Token::TokenType type;
	const char* string;
};





std::vector<TokenAction> Tokenizers{
	Tokens::Greedy(Token::String, "\"", "\"", '\\'),
	Tokens::Greedy(Token::String, "'", "'", '\\'),
	Tokens::While(Token::EndLine, std::isblank) * Tokens::While(Token::EndLine, std::isspace),
	Tokens::Match(Token::BParen),
	Tokens::While(Token::Space, std::isspace),
	Tokens::While(Token::Identifier, std::isalnum),
};



Token Tokenize (char c ) {

	
	

}
