#include "adapter.h"

#include <vector>

void adapter_test() {
	vector<IPrintable*> printeri;
	printeri.push_back(new PrintableAdapter<Printer>(new Printer()));
	printeri.push_back(new PrintableAdapter<Fax>(new Fax()));
	printeri.push_back(new CompliantPrinter());
	
	for (auto printer : printeri) printer->print("Hello, world!");

	for (auto printer : printeri) delete printer;
}

void Printer::print() const {
	cout << "Print internal PrintJob" << endl;
}

void Fax::fax(const char * str) const {
	cout << "Fax & Print " << str << endl;
}

void CompliantPrinter::print(const char * str) const {
	cout << str << endl;
}

template<class T>
inline void PrintableAdapter<T>::print(const char * str) const {
	adapt(ptr, str);
}

template<class T>
template<class U>
void PrintableAdapter<T>::adapt(U * t, const char * str) {
	t->print(str);
}

template<class T>
void PrintableAdapter<T>::adapt(Printer * t, const char *) {
	t->print();
}

template<class T>
void PrintableAdapter<T>::adapt(Fax * t, const char * str) {
	t->fax(str);
}
