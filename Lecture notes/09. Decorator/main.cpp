#include <iostream>

using namespace std;

// Komponenta
class Polje {
public:
	virtual void crtaj() = 0;
};

// Subjekat koji treba da se adaptira
class Input : public Polje {
	void crtaj() {
		cout << "Iscrtavam Input" << endl;
	}
};

// Dekorater
class Dekorater : public Polje {
private:
	Polje* ptrPolje;
public:
	Dekorater(Polje* _ptr): ptrPolje(_ptr){}
	void crtaj() { ptrPolje->crtaj(); }
};

// Konkretan dekorater
class InputIcon : public Dekorater {
	string icon;
public:
	InputIcon(Polje* _p, string _i = "icon_user"): Dekorater(_p), icon(_i) {}
	void crtaj() {
		Dekorater::crtaj();
		cout << " sa ikonicom " << icon << endl;
	}
};

int main() {
	Polje* input = new Input();
	input->crtaj();

	Polje* ikonica = new InputIcon(input);
	ikonica->crtaj();
}