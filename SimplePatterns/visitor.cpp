#include "visitor.h"

#include <iostream>
#include <algorithm>
using namespace std;

template<class T>
KruzniNiz<T>::KruzniNiz(const VNiz<T>& x) : n(x.size()), a(new T[n]) {
	for (size_t i = 0; i < n; i++) a[i] = x[i];
}

template<class T>
void SabiracPosetilac<T>::poseti(VNiz<T>& x) {
	T suma = T();
	for (size_t i = 0; i < x.size(); i++) {
		suma += x[i];
	}
	cout << "Suma niza: " << suma << endl;
}

template<class T>
void SabiracPosetilac<T>::poseti(KruzniNiz<T>& x) {
	T suma = T();
	for (size_t i = 0; i < x.size(); i++) {
		suma += x[i];
	}
	cout << "Suma kruznog niza: " << suma << endl;
}

template<class T>
void RazlikePosetilac<T>::poseti(VNiz<T>& x) {
	T suma = T();
	for (size_t i = 1; i < x.size(); i++) {
		T raz = x[i] - x[i - 1];
		suma += (raz < 0) ? -raz : raz;
	}
	cout << "Suma apsolutnih razlika suseda niza: " << suma << endl;
}

template<class T>
void RazlikePosetilac<T>::poseti(KruzniNiz<T>& x) {
	T suma = T();
	for (size_t i = 0; i < x.size(); i++) {
		T raz = x[i] - x[(i + 1 == x.size()) ? 0 : i + 1];
		suma += (raz < 0) ? -raz : raz;
	}
	cout << "Suma apsolutnih razlika suseda kruznog niza: " << suma << endl;
}

template<class T>
void HasherPosetilac<T>::poseti(VNiz<T>& x) {
	size_t hash_val = 0;
	for (size_t i = 0; i < x.size(); i++) {
		hash_val = hash<pair<T, size_t>>()(make_pair(x[i], hash_val));
	}
	cout << "Hash vrednost niza je: " << hash_val << endl;
}

template<class T>
void HasherPosetilac<T>::poseti(KruzniNiz<T>& x) {
	size_t hash_val = 0, n = x.size();
	size_t* arr = new size_t[n];
	for (size_t i = 0; i < n; i++) {
		size_t hash_val_inner = 0;
		for (size_t j = i; j < i + n; j++) {
			hash_val_inner = hash<pair<T, size_t>>()(
				make_pair(x[i >= n ? i - n : i], hash_val_inner)
				);
		}
		arr[i] = hash_val_inner;
	}
	sort(arr, arr + n);
	for (size_t i = 0; i < n; i++) {
		hash_val = hash<pair<size_t, size_t>>()(make_pair(hash_val, arr[i]));
	}
	delete arr;
	cout << "Hash vrednost kruznog niza je: " << hash_val << endl;
}

void visitor_test() {
	VNiz<int> prvi(3);
	prvi[0] = 1;
	prvi[1] = 2;
	prvi[2] = 3;

	VNiz<char> drugi(3);
	drugi[0] = 's';
	drugi[1] = 'b';
	drugi[2] = 't';

	VNiz<char> treci(3);
	treci[0] = 'b';
	treci[1] = 't';
	treci[2] = 's';

	KruzniNiz<char> drugi_k(drugi);
	KruzniNiz<char> treci_k(treci);

	prvi.docekaj(SabiracPosetilac<int>());
	drugi_k.docekaj(HasherPosetilac<char>());
	treci_k.docekaj(HasherPosetilac<char>());
}
