#pragma once

#include <type_traits>
#include <new>
#include <string>
#include <span>


struct AstNode {

	virtual std::span<AstNode*> nodes() = 0;
	virtual ~AstNode() {}
};

template<int size, int aligment = 8>
struct PolyInlineStorage {
	std::aligned_storage<size, aligment>::type data[1];
	
	template<typename T>
	T* store(T&& object) {
		return new((void*)data) T(std::forward<T>(object));
	}

	template<typename T>
	T* pointer() {
		return reinterpret_cast<T*>(data);
	}

};

template<class T, class Storage = PolyInlineStorage<40>>
struct Poly {
	Storage storage;

	T* operator -> () { return storage.pointer(); }
	T& operator * () { return *storage.pointer(); }
};




/** 
	
	interface Annotation {}

	interface MethodAnnotation : Annotation {
		op canCall (_type: Type): bool;
		op call (method: Method) throws: Method;
	}

	interface TypeAnnotation : Annotation {
		op call (_type: Type): Type;
	}

	interface TypeAnnotation : Annotation {
		op call (_type: Type): Method;
	}

	type MyAnnotation {}

	[MyAnnotation]
	type susu {
		
	}

	interface

	map `type` -> `interface`  {
	
	}


*/