#pragma once

#include <iostream>
using namespace std;

/* Lazin cuveni primer */

struct IPrintable {
	virtual void print(const char*) const = 0;
	virtual ~IPrintable() {}
};

struct Printer {
	void print() const;
};

struct Fax {
	void fax(const char* str) const;
};

struct CompliantPrinter : public IPrintable {
	virtual void print(const char* str) const;
};

template<class T>
class PrintableAdapter : public IPrintable {
public:
	PrintableAdapter(T* ptr) : ptr(ptr) {}
	virtual void print(const char* str) const;
	virtual ~PrintableAdapter() { delete ptr; }
private:
	template<class U>
	static void adapt(U* t, const char* str);

	static void adapt(Printer* t, const char*);

	static void adapt(Fax* t, const char* str);

	T* ptr;
};

void adapter_test();
