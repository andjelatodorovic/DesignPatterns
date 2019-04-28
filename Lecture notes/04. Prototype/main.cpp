/* Ovaj primer je konkretno malo cudnije implementiran zato sto koristi map-u da
 * da bi čuvao prototipe i koristi fabriku za kreiranje istih.
 */

#include <iostream>
#include <map>

using namespace std;


class Celija {
private:
	int size;
public:
	virtual Celija* clone()=0;
	virtual void move()=0;
	int getSize(){return size;}
	void setSize(int i){size=i;}

};

class CelijaA : public Celija{
public:

	virtual Celija* clone(){
		Celija* tmp = new CelijaA();
		tmp->setSize(getSize());
		return tmp;
	}

	virtual void move(){
		cout << "Celija A, velicine " << getSize()  <<" je pomerena" << endl;
	}
};

class CelijaB : public Celija{
public:

	virtual Celija* clone(){
		Celija* tmp = new CelijaB();
		tmp->setSize(getSize());
		return tmp;
	}

	virtual void move(){
		cout << "Celija B, velicine " << getSize()  <<" je pomerena" << endl;
	}
};


class IFabrika{
public:
	virtual Celija* getCelija(char type)=0;
};

class Fabrika{
private:
	map<char,Celija*> array;

public:
	Fabrika(){
		array['A'] = new CelijaA();
		array['B'] = new CelijaB();

		array['A']->setSize(10);
		array['B']->setSize(20);
	}

	Celija* getCelija(char type){
		switch(type){
		case 'A': return array['A']->clone(); break;
		case 'B': return array['B']->clone(); break;
		default: return NULL;
		}
	}
};

int main(){

	Fabrika* f = new Fabrika();

	Celija* ca = f->getCelija('A');
	Celija* cb = f->getCelija('B');

	ca->move();
	cb->move();

	delete ca;
	delete cb;

	return 0;
}
