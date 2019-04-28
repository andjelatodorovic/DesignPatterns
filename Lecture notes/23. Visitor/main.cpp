/*
	Dodavanje funkcija u vec postojecu hijerahiju klasa.

	@Visitor 			Sadrzi operacije Poseti() za svaku podklasu Element
	@ConcreteVisitor	Implementira operacije Poseti(), implrementira se za svaku potklasu
	@Element			Deklarise operaciju Prihvati() posetioca
	@ConcreteElement	Implementira prihvacivanje posetioca
	@ObjectStructure	Definise intefejs za obilazenje elementa i slanje visitora. Compsite cesto

*/

#include <iostream>
#include <vector>
using namespace std;

enum Pay { BOSS = 3500, EMPLOYEE = 1800 };
enum Bonus { BBOSS = 800, BEMPLOYEE = 550 };

class Boss;
class Employee;

/*
Visitor nudi apstrakne medote da poseti KonkretneElemente. Ti metodi se
implementiraju kasnije u konkretnim posetiocima.
*/
class Visitor {
public:
	virtual void Visit(Boss*) = 0;
	virtual void Visit(Employee*) = 0;
	virtual ~Visitor() {}
};

/*
Apstraktni element nudi metod Accept koji ce da nasledjuju svi konkretni elementi
a putem kojeg se prosledjuju posetioci
*/
class Person {
public:
	Person(int _pay) : pay(_pay) {}
	virtual ~Person() {}
	int GetPay() { return pay; }
	virtual void SetPay(int i) { pay = i; }
	virtual void Accept(Visitor*) = 0;
protected:
	int pay;
};

/*
Konkretni element implementira metod Accept(), tako sto mi presledimo visitora
i Konkretni element pozove visitora da poseti samog sebe
*/

class Boss : public Person {
public:
	Boss(int _pay = BOSS) : Person(_pay) {}
	void Accept(Visitor* visitor) {
		visitor->Visit(this);
	}
};

class Employee : public Person {
public:
	Employee(int _pay = EMPLOYEE) : Person(_pay) {}
	void Accept(Visitor* visitor) {
		visitor->Visit(this);
	}
};


class BonusVisitor : public Visitor {
	virtual ~BonusVisitor() {}

	void Visit(Boss* p) {
		p->SetPay(p->GetPay() + BBOSS);
	}

	void Visit(Employee* p) {
		p->SetPay(p->GetPay() + BEMPLOYEE);
	}
};

/*
Objektna struktura ili Kompozicija sadrzi niz elemenata i moguce je pozvati
posetioce na svima njima.
*/

class Staff {
public:
	// Resio sam nekad da dodam destruktor...
	~Staff() {
		for (eiter it = employees.begin(); it != employees.end(); it++) {
			delete (*it);
		}
		employees.clear();
	}

	void Hire(Person* p) {
		employees.push_back(p);
	}

	void Accept(Visitor* v) {
		for (eiter it = employees.begin(); it != employees.end(); it++) {
			(*it)->Accept(v);
		}
	}

	// Samo radi testiranja!!!
	void Print() {
		int i = 1;
		for (eiter it = employees.begin(); it != employees.end(); it++) {
			cout << "Staff #" << i++ << ": " << (*it)->GetPay() << endl;
		}
	}

private:
	typedef vector<Person*>::iterator eiter;
	vector<Person*> employees;
};


int main() {
	Staff* egear = new Staff();

	egear->Hire(new Boss());
	egear->Hire(new Boss(9000));
	egear->Hire(new Employee());
	egear->Hire(new Employee());

	egear->Print();

	BonusVisitor* bonus = new BonusVisitor();
	cout << endl << "Posle Bonusa:" << endl << endl;
	egear->Accept(bonus);

	egear->Print();
}
