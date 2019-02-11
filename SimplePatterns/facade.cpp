#include "facade.h"

#include <iostream>
using namespace std;

void facade_test() {
	cout << "Pozivam ostale funkcije..." << endl;
	Facade f;
	f.Operation1();
	f.Operation2();
}

string SubsystemA::OperationA1() {
	return "Subsystem A, Method A1\n";
}

string SubsystemA::OperationA2() {
	return "Subsystem A, Method A2\n";
}

string SubsystemB::OperationB1() {
	return "Subsystem B, Method B1\n";
}

string SubsystemB::OperationB2() {
	return "Subsystem B, Method B2\n";
}

string SubsystemC::OperationC1() {
	return "Subsystem C, Method C1\n";
}

string SubsystemC::OperationC2() {
	return "Subsystem C, Method C2\n";
}

void Facade::Operation1() {
	cout << ("Operation 1\n" +
		a->OperationA1() +
		a->OperationA2() +
		b->OperationB1());
}

void Facade::Operation2() {
	cout << ("Operation 2\n" +
		b->OperationB2() +
		c->OperationC1() +
		c->OperationC2());
}
