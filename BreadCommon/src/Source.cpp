#include<string>
#include <vector>
#include "bread/Lexer/Lexer.hpp"


template <class T, int InternalStorage = 32>
class Poly {

};


class Module{};
class Type {};
class Concept {};
class ConceptMap {};
class Method {};
class Argument {};
class Member {};
class TranslationUnit {};

class Scope {
public:
	std::string name;
	std::vector<Type> types;
};

class Function : Scope {};



int main() {
	Scope globalScope{ "", {} };
	
	Type type;

	lex();

}
