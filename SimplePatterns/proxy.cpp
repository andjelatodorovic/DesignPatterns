#include "proxy.h"

/* Jos jedan dobar primer: odlozeno izracunavanje */

/* Sve ove stvari su obsolete sa pojavom C++11 */
template<class T, class U>
class PlusOp {
	const T& levi;
	const U& desni;
public:
	PlusOp(const T& le, const U& de) : levi(le), desni(de) {}

	const T& getLevi() const { return levi; }
	const U& getDesni() const { return desni; }

	int getX() const { return levi.getX() + desni.getX(); }
	int getY() const { return levi.getY() + desni.getY(); }
};

class Tacka {
	int x, y;
public:
	Tacka(int xi = 0, int yi = 0) : x(xi), y(yi) {}

	template<class T, class U>
	Tacka(const PlusOp<T, U>& op) : x(op.getX()), y(op.getY()) {}

	template<class T, class U>
	Tacka& operator= (const PlusOp<T, U>& op) {
		x = op.getX();
		y = op.getY();
		return *this;
	}

	int getX() const { return x; }
	int getY() const { return y; }
};

/* Silovanje kompajlera */

template<class T, class U>
PlusOp<PlusOp<T, U>, Tacka> operator+ (const PlusOp<T, U>& levi, const Tacka& p) {
	return PlusOp<PlusOp<T, U>, Tacka>(levi, p);
}

template<class T, class U>
PlusOp<Tacka, PlusOp<T, U>> operator+ (const Tacka& p, const PlusOp<T, U>& desni) {
	return PlusOp<Tacka, PlusOp<T, U>>(p, desni);
}

template<class T, class U, class V, class W>
PlusOp<PlusOp<T, U>, PlusOp<V, W>> operator+ (const PlusOp<T, U>& levi, const PlusOp<V, W>& desni) {
	return PlusOp<PlusOp<T, U>, PlusOp<V, W>>(levi, desni);
}

PlusOp<Tacka, Tacka>
operator+(const Tacka& levi, const Tacka& desni) {
	return PlusOp<Tacka, Tacka>(levi, desni);
}

void proxy_test() {
	{
		SmartPtr<Proxyn> p = new Proxyn(25);

		{
			p = new Proxyn(169);
		}
	}

	Tacka t1(1, 2), t2(3, 4), t3(5, 6);
	Tacka t = (t1 + t2) + (t3 + t1);
	cout << t.getX() << ", " << t.getY() << endl;
}

Proxyn::Proxyn(int x) {
	cout << "Konstruktor " << x << "\n";
}

Proxyn::~Proxyn() {
	cout << "Destruktor\n";
}

template<class T>
void SmartPtr<T>::detach() {
	--*br;
	if (*br == 0) {
		delete ptr;
		delete br;
	}
}

template<class T>
SmartPtr<T>& SmartPtr<T>::operator= (const SmartPtr& other) {
	if (this != &other) {
		detach();
		ptr = other.ptr;
		br = other.br;
		++*br;
	}
	return *this;
}