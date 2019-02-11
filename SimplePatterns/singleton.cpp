#include "singleton.h"
#include <cstdlib>

#include <iostream>
#include <thread>
using namespace std;

Singleton& Singleton::Instance() {
	//lokalna staticka promenljiva
	this_thread::sleep_for(500ms);
	static Singleton inst;
	return inst;
}

void Singleton::Operation() {
	cout << "Ja sam dobar! Moja adresa: " << this << endl;
}

LosSingleton& LosSingleton::Instance() {
	if (ptr == 0) {
		this_thread::sleep_for(500ms);
		ptr = new LosSingleton;
	}
	return *ptr;
}

void LosSingleton::Operation() {
	cout << "Ja sam los! Moja adresa: " << this << endl;
}

LosSingleton* LosSingleton::ptr = 0;

void koristi_los_singleton() {
	LosSingleton::Instance().Operation();
}

void koristi_dobar_singleton() {
	Singleton::Instance().Operation();
}

void singleton_test() {
	
	thread t1(koristi_los_singleton), t2(koristi_los_singleton);

	thread t3(koristi_dobar_singleton), t4(koristi_dobar_singleton);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}