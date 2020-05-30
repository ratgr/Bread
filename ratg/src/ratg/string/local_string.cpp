#include "local_string.h"

void ratg::local_string::own(){
	if (ownsPtr) return;

	ownsPtr = true;
	auto* storage = new char[size + 1]();
	
	strncpy(storage, ptr, size);
	storage[size] = 0;
}

ratg::local_string ratg::local_string::ref()
{
	return local_string{.ptr = ptr, .size = size, .ownsPtr = false};
}

ratg::local_string ratg::local_string::copy()
{
	auto* storage = new char[size + 1]();
	return local_string{ .ptr = storage, .size = size, .ownsPtr = false };
}

inline ratg::local_string::~local_string() {
	if (ownsPtr) { delete[] ptr; }
}
