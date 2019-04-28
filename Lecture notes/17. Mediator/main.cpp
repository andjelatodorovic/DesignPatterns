/*

	Ideja ovog uzorka je da spreci direktnu komunikaciju dva objekta, vec se sva
	komunikacija obavlja preko MEDIATORA, tako sto kaze kome hoce da se obrati
	i MEDIATOR mu prosledi "poruku".

	@ Mediator				Interfase za komunikaciju sa 'kolegama'.
	@ ConsreteMediator		Implementira komunikaciju izmedju kolega, zna kolege.
	@ Colleague				Svaki kolega zna svog mediatora i preko njega komunicira sa
							drugim kolegama.

 */


#include <iostream>
#include <string>
#include <map>

using namespace std;

class iUser;

// Mediator
class iChat {
public:
	virtual void Register(iUser*) = 0;
	virtual void Send(const string&, const string&, const string&) = 0; // Metoda za komuniciranje sa kolegama
};


// Interfase za Colleague
class iUser {
public:
	iUser(const string& _username): username(_username){}
	void EnterRoom(iChat* _room) { room = _room; }
	string Username() {return username; }

	// Ovo je funkcija koja poziva mediatora (Room)
	virtual void SendMessage(const string& to, const string& msg) {
		if(room != NULL)
			room->Send(to, username, msg);
	}

	// Ovu funkciju sam cisto dodao ja zato sto sam ja... Nije potrebna
	virtual void Reply(const string& msg) {
		if(!lastMsg.empty()) {
			SendMessage(lastMsg, msg);
		}
		else
			cout << endl << " -------------------- NEMAS KOME DA ODGOVORIS ----------------------" << endl;
	}
	virtual void Receive(const string&, const string&) = 0;
protected:
	string username;
	iChat* room; // OBAVEZNO: zna svog mediatora

	string lastMsg;
};

// Colleague
class NormalUser : public iUser {
public:
	NormalUser(const string& _username) : iUser(_username){}

	void Receive(const string& from, const string& msg) {
		cout << endl << "To: " << username << " (normal)" << endl << "Message: " << msg << endl << " From: " << from << endl;

		if(lastMsg != from) {
			lastMsg = from;
		}
	}
};

// Colleague
class AdminUser : public iUser {
public:
	AdminUser(const string& _username) : iUser(_username){}

	void Receive(const string& from, const string& msg) {
		cout << endl << "To: " << username << " (admin)" << endl << "Message: " << msg << endl << " From: " << from << endl;

		if(lastMsg != from) {
			lastMsg = from;
		}
	}
};


// ConcreteMediator
class Chat : public iChat {
public:
	void Register(iUser* user) {
		user->EnterRoom(this);
		people[user->Username()] = user;
		cout << "USER: " << user->Username() << " has joined the chatroom" << endl;
	}

	// Kad Kolega pozove mediatora on poziva ovu funkciju i MEDIATOR salje poruku korisniku
	void Send(const string& to, const string& from, const string& msg) {
		if(people.find(to) != people.end()) {
			people[to]->Receive(from, msg);
		}
	}
protected:
	map<string, iUser*> people; // MEDIATOR ZNA SVE KOLEGE
};

int main() {
	iUser* marko = new NormalUser("maverick");
	iUser* mladen = new AdminUser("msia3");
	iUser* aca = new NormalUser("batica");
	iUser* manic = new NormalUser("manic12");
	iUser* branko = new NormalUser("angeldead");

	iChat* egear = new Chat();

	egear->Register(marko);
	egear->Register(mladen);
	egear->Register(aca);
	egear->Register(manic);
	egear->Register(branko);

	manic->SendMessage("batica", "Mislim da sam pokvario nesto");
	aca->Reply("STA SI POKVARIOOOO???");
	manic->Reply("Prebacio sam /usr u /bin");
	mladen->Reply("Sad cu te banujem!"); // Namerna greska
	manic->SendMessage("msia3", "Izbaci ovog acu");
	mladen->Reply("Sad cu ga banujem!");
	marko->SendMessage("msia3","hahahahah");
	branko->SendMessage("msia3","tri tacke");
}
