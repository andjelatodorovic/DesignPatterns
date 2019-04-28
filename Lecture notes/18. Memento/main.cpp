/*
	Memento se koristi da bi cuvali prethodno stanje objekta

	@ Originator 		Subjekat, koji zna da sacuva samog sebe. Na njemu se poziva funkcija Restore()
	@ Caretaker			Onaj koji cuva listu kreiranih podsetnika
	@ Memento			Jedan restore point (snapshot), koji cuva sve potrebno da se rekonstruise objekat
*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Memento {
public: // Ovo bi trebalo da bude privatno a prijatelj ove klase da bude subjekat
	Memento(string _op) : operation(_op){}
	string GetState() { return operation; }
private:// OVO TREBA PRIVATE;
	string operation; // Ovo je jedino stanje koje pamtim, dovoljno da vratim objekat.
};

// Cuva Mementa.
class Caretaker {
private:
	vector<Memento*> history;
	typedef vector<Memento*>::iterator iter;
public:
	~Caretaker() {
		for (iter i = history.begin(); i != history.end(); i++) {
			delete *i;
		}
	}

	// Dodaje mementa u svoju istoriju
	void AddPoint(Memento* m) {
		history.push_back(m);
	}

	// Ovo sam ja dodao kako bih video sva prethodna stanja
	void History() {
		cout << "Istorija:" << endl;
		int j = 0;
		for (iter i = history.begin(); i != history.end(); i++) {
			cout << "#" << j++ << ": " << (*i)->GetState() << endl;
		}
		cout << endl;
	}

	// Ovoj funkciji nije ovde mesto, zato sto jedini nacin na koji bi smelo da se vrati
	// stranje je preko subjekta, ja sam ovo dodao kako bi mogao da vratim na N-tu poziciju!!!
	Memento* GetHistory(int i) {
		if (history.size() == 0) throw("Nema istorije");
		if (i > history.size()) throw("Unet broj je prevelik");
		history.erase(history.begin() + i+1, history.end());
		return history[i];
	}
};

Caretaker* history = new Caretaker(); // Definisem globalnu istoriju za program

class Operation {
public:
	Operation(string _op) : operation(_op), result(Converter(_op)) {
		history->AddPoint(new Memento(operation));
		//cout << operation << " = " << result << endl;
	};

	// Ovo funkcija bi trebala da vraca prethodno stanje (RoleBack) a ne N-to stanje.
	void Restore(int n) {
		operation = history->GetHistory(n)->GetState();
	};

	double getResult() {return result; }
private:

	string operation;
	double result;

	// Funkcija koja je totalno visak, tu je samo radi ovog primera.
	// Prebacuje String oblika (int<znak>int) u rezultat.
	double Converter(string eq) {
		int i = 0;
		char op;

		while (isdigit(eq[i]) != 0) {
			i++;
			op = eq[i];
		}

		double left = stod(eq.substr(0, i));
		double right = stod(eq.substr(i + 1, eq.length()));

		switch (op) {
		case '+': return left + right;
		case '-': return left - right;
		case '*': return left * right;
		case '/': return left / right;
		default:
			cout << "OPERATOR '" << op << "' NIJE POZNAT";
			return 0.1;
		}
	}
};

int main() {
	string val;
	cin >> val;
	Operation* t = new Operation(val);
	do {
		cin >> val;
		if (val != "h")
				t = new Operation(val);
	} while (val != "h");
	try{

		history->History();
		int n;
		cin >> n;
		t->Restore(n);
		history->History();
	} catch (const char* e) {
		cout << "ERROR: " << e << endl;
	}
}
