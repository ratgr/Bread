#pragma once
#include <cstdint>


namespace ratg {

}

enum BindingType {
	Constant = 0b0001,
	Variable = 0b0010,
	Reference= 0b0100,
};



struct Annotation;
struct TypeInfo;


struct AnnotatedInfo {
	const char*  name;
	Annotation* annotation;
};


struct MemberInfo : AnnotatedInfo {
	TypeInfo* Type;
	BindingType binding;
};

struct TypeInfo : AnnotatedInfo {
	MemberInfo d ;
};



