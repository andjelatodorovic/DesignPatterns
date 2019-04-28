/*
	Lanac odgovornosti nam dopusta da ne vezujem objekat za JEDAN rezresivaca, vec da mozemo da
	vezemo na lanac rezresivaca koji ce ga resiti ako je u mogucnosti

	@ Handler 				Definise interfase za razresavanje zahteva.
	@ ConcreteHandler		Konkretan razresivac, izvodi se iz Handler-a. Zna koji zahtev moze da obradi.
							Treba da pokazuje na njegovog sledbenika.
*/

#include <iostream>
#include <string>
using namespace std;

enum KeyLoggerType { INFO, ERROR, DEBUG, UNDEFINED }; // Definisao sam tipoove zahteva preko enum-a, da mi bude lakse.

// Ovo je Handler
class Logger {
public:
	Logger() : nextLogger(NULL) {}
	Logger(KeyLoggerType _type) : type(_type), nextLogger(NULL){}
	void setLogger(Logger *l) {
		nextLogger = l;
	}
	virtual void print(KeyLoggerType t, string &m) { // Ovo je funkcija koja treba da bude obradjena za zahtev
		if (nextLogger != NULL) {
			nextLogger->print(t, m);
		}
		else {
			cout << "We can't print this message!" << endl;
		}
	}

	bool isType(const KeyLoggerType _t) { // Koristim radi lakse provere tipe.
		return type == _t;
	}

private:
	KeyLoggerType type; // Ovo sam ja uveo kao tip zahteva koji stize
	Logger* nextLogger; // VRLO BITNO, ovde cuvamo sledbenika (ako postoji) i tako pravimo lanac.
};

// Konkretni razresavaci:

class InfoLogger : public Logger {
public:
	InfoLogger() : Logger(INFO){}
	void print(KeyLoggerType t, string& m) {
		if (isType(t)) {
			cout << "Info: " << m << endl;
		}
		else {
			Logger::print(t, m);
		}
	}

};

class ErrorLogger : public Logger {
public:
	ErrorLogger() : Logger(ERROR){}
	void print(KeyLoggerType t, string& m) {
		if (isType(t)) {
			cout << "Error: " << m << endl;
		}
		else {
			Logger::print(t, m);
		}
	}

};

class DebugLogger : public Logger {
public:
	DebugLogger() : Logger(DEBUG){}
	void print(KeyLoggerType t, string& m) {
		if (isType(t)) {
			cout << "Debug: " << m << endl;
		}
		else {
			Logger::print(t, m);
		}
	}

};

int main(){
	Logger *logger = new Logger();
	Logger *info = new InfoLogger();
	Logger *error = new ErrorLogger();
	Logger *debug = new DebugLogger();

	logger->setLogger(info);
	info->setLogger(error);
	error->setLogger(debug);

	string msg = "It works";
	logger->print(DEBUG, msg);

	msg = "Doslo je do greske";
	logger->print(ERROR, msg);

	// Ovo nece da se odstampa zato sto ne postoji
	// handler za ovaj tip.
	msg = "Fun fun funnnnnn";
	logger->print(UNDEFINED, msg);

	return 0;
}
