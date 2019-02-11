#pragma once

#include <iostream>
using namespace std;

template<class T>
class SmartPtr {
	T* ptr;
	size_t* br;
	void detach();
public:
	SmartPtr(T* ptr) : ptr(ptr), br(new size_t(1)) {}
	SmartPtr(const SmartPtr& other) : ptr(ptr), br(br) { ++*br; }
	SmartPtr& operator= (const SmartPtr& other);
	T* operator-> () { return ptr; }
	T& operator* () { return *ptr; }
	const T* operator-> () const { return ptr; }
	const T& operator* () const { return *ptr; }
	~SmartPtr() { detach(); }
};

struct Proxyn {
	Proxyn(int x);
	~Proxyn();
};

void proxy_test();

