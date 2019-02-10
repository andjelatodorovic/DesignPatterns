#include<iostream>
#include<sstream>

using namespace std;

class Display{

private:
	double temp;

public:
	Display() : temp(0) {}

	double getTemp() const
	{
		return temp;
	}

	void setTemp(double x)
	{
		temp = x;
	}

	~Display() {}

};

class Auto;
class Sranje
{
public:
	virtual string getStanje() = 0;
	virtual void ubrzaj(Auto*) = 0;
	virtual void koci(Auto*) = 0;
};

class Auto{

private:
	double brzina;
	Display* dis;
	double maxtemp;
	Sranje * stanje;

public:
	Auto() : brzina(0), maxtemp(57), dis(new Display() ) {}

	void setSranje(Sranje* s) { stanje = s; }

	string getSranje() const
	{
		return stanje->getStanje();
	}

	double getBrzina() const
	{
		return brzina;
	}

	void setBrzina(double x)
	{
		brzina = x;
	}

	void ubrzaj()
	{
		brzina+=10;
		cout << brzina << endl;
		dis->setTemp((dis->getTemp()) + 7);
		koci();
	}

	void koci()
	{
		if (dis->getTemp() > maxtemp)
		{
			brzina = 0;
			cout << "KOCIIIIIIIII" << endl;
		}
		else
			cout << "Samo cepaj nista se ne pusi..." << endl;
	}

	~Auto()
	{
		delete dis;
	}
};


class Ugasen : public Sranje
{
public:
	string getStanje() { return "Ugasen"; }

	virtual void ubrzaj(Auto* mobil )
	{
		cout << "Ne moze;" << endl;
	}

	virtual void koci(Auto* mobil)
	{
		cout << "Ne moze;" << endl;
	}

};

class Normalno : public Sranje
{
public:
	string getStanje() { return "Normalno"; }
	virtual void ubrzaj(Auto * mobil)
	{
		mobil->ubrzaj();
		cout << "Ubrzajem.." << endl;
	}
	
	virtual void koci(Auto* mobil)
	{
		mobil->koci();
		cout << "Ukocajem.." << endl;
	}
};


int main() {

	Auto mobil;
	Normalno sranje;
	mobil.setSranje(&sranje);
	for (int i = 1; i; i++)
	{
		cout << "radim nesto " << i << endl;
	}
	cout << mobil.getSranje()<<endl;

	/*sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);
	sranje.ubrzaj(&mobil);

	sranje.koci(&mobil);
	sranje.koci(&mobil);
	sranje.koci(&mobil);
	sranje.koci(&mobil);
	sranje.koci(&mobil);
	sranje.koci(&mobil);*/





	system("pause");
	return 0;
}