#pragma once

#include <vector>
using namespace std;

template<class T>
class VNiz;

template<class T>
class KruzniNiz;

template<class T>
class IPosetilac {
public:
	virtual void poseti(VNiz<T>&) = 0;
	virtual void poseti(KruzniNiz<T>&) = 0;
	virtual ~IPosetilac() {}
};

template<class T>
class IVisitable {
public:
	virtual ~IVisitable() {}
	virtual void docekaj(IPosetilac<T>&) = 0;
};

template<class T, class Izvedena>
class CRTPVisitable : public IVisitable<T> {
public:
	virtual ~CRTPVisitable() {}
	virtual void docekaj(IPosetilac<T>& pos) {
		pos.poseti(*(Izvedena*)this);
	}
};

/* 
 * Nizovi dolaze u dve varijante: Obicni i kruzni. 
 * I nad jednim i nad drugim moze mnogo toga da se radi.
 * Zato koristimo visitor pattern.
 */

template<class T>
class VNiz : public CRTPVisitable<T, VNiz<T>> {
	size_t n;
	T* a;
public:
	explicit VNiz(size_t n) : n(n), a(new T[n]) {};
	~VNiz() { delete[] a; }
	size_t size() const { return n; }
	T& operator[] (size_t x) { return a[x]; }
	T operator[] (size_t x) const { return a[x]; }
};

template<class T>
class KruzniNiz : public CRTPVisitable<T, KruzniNiz<T>> {
	size_t n;
	T* a;
	KruzniNiz() = default;
public:
	KruzniNiz(const VNiz<T>& x);
	~KruzniNiz() { delete[] a; }
	size_t size() const { return n; }
	T& operator[] (size_t x) { return a[x]; }
	T operator[] (size_t x) const { return a[x]; }
};

/* Primer tri visitora (naravno moze tu jos svasta da se radi):
 * Sabirac, racunac sume apsolutnih razlika susednih, hasher.
 */

template<class T>
class SabiracPosetilac : public IPosetilac<T> {
public:
	SabiracPosetilac() {}
	~SabiracPosetilac() {}
	virtual void poseti(VNiz<T>& x);
	virtual void poseti(KruzniNiz<T>& x);
};

template<class T>
class RazlikePosetilac : public IPosetilac<T> {
public:
	RazlikePosetilac() {}
	~RazlikePosetilac() {}
	virtual void poseti(VNiz<T>& x);
	virtual void poseti(KruzniNiz<T>& x);
};

template<class T, class U>
struct hash<pair<T, U>> {
	size_t operator() (const pair<T,U>& p) {
		return hash<T>()(p.first) + (size_t)47398173497198437ll * hash<U>()(p.second);
	}
};

template<class T>
class HasherPosetilac : public IPosetilac<T> {
public:
	HasherPosetilac() {}
	~HasherPosetilac() {}
	virtual void poseti(VNiz<T>& x);
	virtual void poseti(KruzniNiz<T>& x);
};

void visitor_test();
