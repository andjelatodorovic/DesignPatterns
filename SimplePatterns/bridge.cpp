#include "bridge.h"

#include <iostream>
using namespace std;

template<class T>
bool LancanaLista<T>::jePrazna() {
	return glava == 0;
}

template<class T>
void LancanaLista<T>::dodaj(T x) {
	glava = new Cvor<T>(x, glava);
}

template<class T>
T LancanaLista<T>::uzmi() {
	T tmp = glava->info;
	auto p = glava;
	glava = glava->next;
	delete p;
	return tmp;
}

template<class T>
LancanaLista<T>::~LancanaLista() {
	while (glava) {
		auto p = glava;
		glava = glava->next;
		delete p;
	}
}

template<class T>
void Niz<T>::povecaj() {
	T* p = new T[kapac * 2];
	for (int i = 0; i < top; i++) {
		p[i] = data[i];
	}
	kapac *= 2;
	delete[] data;
	data = p;
}

template<class T>
void Niz<T>::dodaj(T x) {
	if (top == kapac) povecaj();
	data[top++] = x;
}

template<class T>
T Niz<T>::uzmi() {
	return data[--top];
}

template<class T>
Niz<T>::~Niz() {
	delete[] data;
}

void bridge_test() {
	Stek<int> stek;
	Stek2<int> stek_lista(new LancanaLista<int>);
	for (int i = 0; i < 5; i++) {
		stek.push(i);
		stek_lista.push(i);
	}
	for (int i = 0; i < 5; i++) {
		cout << stek.pop() << ' ' << stek_lista.pop() << endl;
	}
}