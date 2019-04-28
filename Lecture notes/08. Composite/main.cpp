#include <iostream>
#include <vector>
#include <stdlib.h> // srand, rand
#include <time.h> // time
using namespace std;

// Komponenta
class Vojnik {
public:
	virtual void napadni() = 0;
	virtual void odbrani() = 0;
};

// List
class Pesak : public Vojnik {
public:
	void napadni() { cout << "Pesak napada" << endl; }
	void odbrani() { cout << "Pesak se brani" << endl; }
};

// List 2
class Strelac : public Vojnik {
public:
	void napadni() { cout << "Strelac napada" << endl; }
	void odbrani() { cout << "Strelac se brani" << endl; }
};

// Komponenta
class Vod : public Vojnik {
protected:
	vector<Vojnik*> vojska; // Ovde idu listovi
public:
	void regrutuj(Vojnik* v) {
		vojska.push_back(v);
	}
	void napadni() {
		for(int i=0; i < vojska.size(); i++)
			vojska[i]->napadni();
	}

	void odbrani() {
		for(int i=0; i < vojska.size(); i++)
			vojska[i]->odbrani();
	}
};

int main() {
	srand (time(NULL));

	Vod* vod1 = new Vod();

	for(int i = 0; i < 10; i++) {
		if(rand() % 2)
			vod1->regrutuj(new Strelac());
		else
			vod1->regrutuj(new Pesak());
	}

	vod1->napadni();
	vod1->odbrani();
}