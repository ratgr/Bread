#pragma once
#include <optional>
#include <type_traits>
#include <ratg/typetraits/flatten_variant.hpp>
#include <cppcoro/generator.hpp>


template <class T> struct LamdaTokenizer {

	using ValueType = std::remove_reference_t<decltype( (T{}) ("", std::declval<int&>(), std::declval<int&>()).value())>;

	LamdaTokenizer(T var) {}
	LamdaTokenizer() {}

	static auto Tokenize(const char* c, int& line, int& column) {
		return T{}(c, line, column);
	}

};

template <class T> struct Tokenizer {

	static auto Tokenize(const char* c, int& line, int& column) {
		return T::Tokenize(c, line, column);
	}

};

template<class T, class S>
auto operator | (Tokenizer<T> a, Tokenizer<S> s) {
	return LamdaTokenizer([](const char* c, int& line, int& column) -> std::optional<std::variant<T, S>> {
		auto resA = Tokenizer<T>::Tokenize(c, line, column);
		if (resA.has_value()) return resA.value();
		return Tokenizer<S>::Tokenize(c, line, column);
	});
}

template<class T, class S>
auto operator | (LamdaTokenizer<T> a, Tokenizer<S> s) {
	return LamdaTokenizer([](const char* c, int& line, int& column) -> std::optional<std::variant<decltype(a)::ValueType,S>> {
		auto resA = LamdaTokenizer<T>::Tokenize(c, line, column);
		if (resA.has_value()) return resA.value();
		return Tokenizer<S>::Tokenize(c, line, column);
	});
}

class Token {
public:


	template<class T>
	struct TokenBase {
		int line;
		int column;
		const char* begin;
		int size;

		std::optional<T> Tokenize(const char* c, int line, int column);

	};

	struct Identifier : public TokenBase<Identifier> {
		int Tokenize(std::string_view str) {
			int size = 0;
			for (char c : str) {
				if (std::isalnum(c) || c == '_') size++;
				else break;
			}
			return size > 0 ? size : -1;
		}
	};

	struct Number {
		int Tokenize(const char* c) {}
	};

	struct Symbol {
		int Tokenize(const char* c) {}
	};



};

using TokenParser = decltype (
	Tokenizer<Token::Symbol>{}
	| Tokenizer<Token::Number>{}
	| Tokenizer<Token::Identifier>{}
);


template<class T>
std::optional<T> Token::TokenBase<T>::Tokenize(const char* c, int line, int column) {
	T token = {};
	token.begin = c; 
	token.column = column; 
	token.line = line; 
	int size = token.Tokenize(c);

	if (size >= 0) return token;
	return std::nullopt;
};






