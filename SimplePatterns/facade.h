#pragma once

#include <string>
#include <iostream>
using namespace std;

/* Jedan veoma cheesy primer uzet direktno sa wikipedije */

struct SubsystemA {
	string OperationA1();
	string OperationA2();
};

struct SubsystemB {
	string OperationB1();
	string OperationB2();
};

struct SubsystemC {
	string OperationC1();
	string OperationC2();
};

class Facade {
	SubsystemA* a;
	SubsystemB* b;
	SubsystemC* c;
public:
	Facade() : a(new SubsystemA()), b(new SubsystemB()), c(new SubsystemC())
		{}
	void Operation1();
	void Operation2();
};

void facade_test();