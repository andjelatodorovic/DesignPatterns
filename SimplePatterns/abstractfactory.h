#pragma once

#include <map>
#include <iostream>
using namespace std;

class AbsProduct {
public:
	virtual ~AbsProduct() {}
	virtual int Get() = 0;
};

class Product_A : public AbsProduct {
public:
	int Get() {	return 525; }
};

class Product_B : public AbsProduct {
public:
	int Get() {	return 6487; }
};

template <class T>
class Creator {
public:
	virtual ~Creator() {}
	virtual T* Create() = 0;
};

template <class Derived, class Base>
class DerivedCreator : public Creator<Base> {
public:
	virtual Base* Create() { return new Derived; }
};

template <class T>
class Factory {
public:
	void Register(int id, Creator<T>* ptrToCreator);
	T* Create(int id);
	~Factory();
private:
	map<int, Creator<T>*> creatorRegister;
};

void abstractfactory_test();
