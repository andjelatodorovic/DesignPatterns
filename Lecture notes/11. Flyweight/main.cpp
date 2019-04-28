#include <iostream>
#include <map>

using namespace std;

// IMuva
class Slovo {
public:
	virtual void prikazi(int) = 0; // Extrinsic state
	virtual ~Slovo() {}
protected:
	Slovo(char _simbol): simbol(_simbol){}
	// Intrinsic state
	char simbol;
};

// Konkretna muva
class SlovoA : public Slovo {
public:
	SlovoA(): Slovo('A'){}
	void prikazi(int font) {
		cout << "Prikazujem slovo '" << simbol << "' font-size: " << font << "px" << endl;
	}
};

class SlovoB : public Slovo {
public:
	SlovoB(): Slovo('B'){}
	void prikazi(int font) {
		cout << "Prikazujem slovo '" << simbol << "' font-size: " << font << "px" << endl;
	}
};

// Fabrika muva
class Fabrika {
public:
	Slovo* uzmiSlovo(char _slovo) {
		if(slova.find(_slovo) == slova.end()) {
			switch(_slovo) {
				case 'A': slova[_slovo] = new SlovoA();
				case 'B': slova[_slovo] = new SlovoB();
			}
		}
		return slova[_slovo];
	}
protected:
	map<char, Slovo*> slova;
};

int main() {
	Fabrika* azbuka = new Fabrika();
	Slovo* slovo = azbuka->uzmiSlovo('A');

	slovo->prikazi(36);
}