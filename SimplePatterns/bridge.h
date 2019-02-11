#pragma once

template<class T>
struct IMemorija {
	virtual void dodaj(T) = 0;
	virtual T uzmi() = 0;
	virtual ~IMemorija() {}
};

template<class T>
struct Cvor {
	T info;
	Cvor<T>* next;
	Cvor(T info, Cvor<T>* next) : info(info), next(next) {}
};

template<class T>
class LancanaLista : public IMemorija<T> {
	Cvor<T>* glava;
public:
	bool jePrazna();
	LancanaLista() : glava(0) {}
	void dodaj(T x);
	T uzmi();
	~LancanaLista();
};

template<class T>
class Niz : public IMemorija<T> {
	T* data;
	int top;
	int kapac;
	static const int INIT_SIZE = 2;

	void povecaj();
public:
	Niz() : data(new T[INIT_SIZE]), top(0), kapac(INIT_SIZE) {}
	void dodaj(T x);
	T uzmi();
	~Niz();
};

// I sada mozemo da implementiramo stek

template<class T, template<typename> class Memorija = Niz>
class Stek {
	Memorija<T> mem;
public:
	void push(T x) {
		mem.dodaj(x);
	}

	T pop() {
		return mem.uzmi();
	}
};

// Jos jedan stek, koji vise lici na ono sto bi moglo da se ocekuje u Javi

template<class T>
class Stek2 {
	IMemorija<T>* mem;
public:
	Stek2(IMemorija<T>* mem) : mem(mem) {}

	void push(T x) {
		mem->dodaj(x);
	}

	T pop() {
		return mem->uzmi();
	}

	~Stek2() { delete mem; }
};

void bridge_test();
